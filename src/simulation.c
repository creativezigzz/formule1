//
// Created by Loulou on 29/12/2021.
//

#include "../inc/simulation.h"
#include "../inc/simulation_utils.h"
//#include "../inc/car_stuff.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include <sys/ipc.h>
//#include <sys/sem.h>
#include <sys/shm.h>

#include <string.h>

int min_pit = 20000;
int max_pit = 25000;


int start_sem() {
    key_t semKey = ftok(".", 34);
    int this_sem_id = semget(semKey, 2, IPC_CREAT | 0666);

    if (semKey < 0) {
        perror("Error semid ");
        exit(1);
    }

    semctl(this_sem_id, 0, SETVAL, 1);
    semctl(this_sem_id, 1, SETVAL, 1);

    return this_sem_id;
}

void wait(int i, int this_sem_id, struct sembuf op) { //Met en pause le Thread
    op.sem_num = i;

    op.sem_op = -1;

    op.sem_flg = SEM_UNDO;

    semop(this_sem_id, &op, 1);
}


void post(int i, int this_sem_id, struct sembuf op) { //Enlève le thread de la liste d'attente
    op.sem_num = i;

    op.sem_op = 1;

    op.sem_flg = SEM_UNDO;

    semop(this_sem_id, &op, 1);
}

void begin_reading(int this_sem_id, struct sembuf op,int nbr_reader) { //Début section critique
    wait(0, this_sem_id, op);

    nbr_reader++;

    if (nbr_reader == 1) {

        wait(1, this_sem_id, op);
    }

    post(0, this_sem_id, op);
}

void stop_reading(int this_sem_id, struct sembuf op, int nbr_reader) { //Fin section critique
    wait(0, this_sem_id, op);

    nbr_reader--;

    if (nbr_reader == 0) {

        post(1, this_sem_id, op);
    }

    post(0, this_sem_id, op);
}
void sort(Car drivers[NUMBER_OF_PILOTES], Car *circuit, int race_car_number,struct sembuf operation,int new_sem_id,int nbr_reader){

    Car temp; //Structure temporaire pour stocker les voitures en cours de tri

    begin_reading(new_sem_id, operation,nbr_reader); //Section critique début

    memcpy(drivers, circuit, race_car_number * sizeof(struct Car));

    stop_reading(new_sem_id, operation,nbr_reader); //Section critique fin

    int i, j, k;

    for (i = race_car_number / 2; i > 0; i = i / 2){ //On divise la liste des pilotes en 2

        for (j = i; j < race_car_number; j++){

            for(k = j - i; k >= 0; k = k - i){

                if (drivers[k+i].bestLap >= drivers[k].bestLap)

                    break;

                else{

                    temp = drivers[k];

                    drivers[k] = drivers[k+i];

                    drivers[k+i] = temp;

                }
            }
        }
    }
}
void sort_by_total(Car drivers[NUMBER_OF_PILOTES], Car *circuit, int race_car_number,struct sembuf operation,int new_sem_id,int nbr_reader){

    Car temp; //Structure temporaire pour stocker les voitures en cours de tri

    begin_reading(new_sem_id, operation,nbr_reader); //Section critique début

    memcpy(drivers, circuit, race_car_number * sizeof(struct Car));

    stop_reading(new_sem_id, operation,nbr_reader); //Section critique fin

    int i, j, k;

    for (i = race_car_number / 2; i > 0; i = i / 2){ //On divise la liste des pilotes en 2

        for (j = i; j < race_car_number; j++){

            for(k = j - i; k >= 0; k = k - i){

                if (drivers[k+i].totalTime >= drivers[k].totalTime)

                    break;

                else{

                    temp = drivers[k];

                    drivers[k] = drivers[k+i];

                    drivers[k+i] = temp;

                }
            }
        }
    }
}

void affichage(Car drivers[NUMBER_OF_PILOTES], int race_car_number, Car * circuit,struct sembuf op,int new_sem_id, int nbr_reader,int t_sort) {
    if(t_sort){
        sort_by_total(drivers, circuit, race_car_number, op, new_sem_id, nbr_reader);
    }
    else{
        sort(drivers, circuit, race_car_number, op, new_sem_id, nbr_reader);
    }


    double bestS1 = 99.0;

    double bestS2 = 99.0;

    double bestS3 = 99.0;

    double bestLap = 999.0;

    int j;



    //Affichage à l'écran
    printf("|N°\t|S1\t|S2\t|S3\t|Tour\t\t|Best Tour\t|PIT\t|OUT\t|\n");

    printf("\n");

    for (j = 0; j < race_car_number; j++) {
        Car *pilote = drivers + j;
        //Affiche l'id du pilote
        printf("|%d\t", pilote->ID);

        //Affiche le temps S1
        (pilote->S1 == 0) ? printf("|NULL\t") : printf("|%.3f\t", pilote->S1);

        //Affiche le temps S2
        (pilote->S2 == 0) ? printf("|NULL\t") : printf("|%.3f\t", pilote->S2);

        //Affiche le temps S3
        (pilote->S3 == 0) ? printf("|NULL\t") : printf("|%.3f\t", pilote->S3);

        //Affiche le temps du tour
        (pilote->lap < 100.000) ? printf("|%.3f\t\t", pilote->lap) : printf("|%.3f\t", pilote->lap);

        //Affiche le meilleur temps
        (pilote->bestLap < 100.000) ? printf("|%.3f\t\t", pilote->bestLap) : printf("|%.3f\t",
                                                                                    pilote->bestLap);

        //Affiche le nombre de pit du pilote
        (pilote->isPit != 0) ? printf("|%d\t", pilote->isPit) : printf("|0\t");


        //Affiche si le pilote est out
        (pilote->isOut == 1) ? printf("|X\t|\n") : printf("|\t|\n");

        //Fin affichage
    }
    //Définir les meilleurs temps

    for (j = 0; j < race_car_number; j++) {
        Car *pilote = drivers + j;
        bestS1 = (bestS1 > pilote->S1 && pilote->S1 != 0) ? pilote->S1 : bestS1;

        bestS2 = (bestS2 > pilote->S2 && pilote->S2 != 0) ? pilote->S2 : bestS2;

        bestS3 = (bestS3 > pilote->S3 && pilote->S3 != 0) ? pilote->S3 : bestS3;



    }

    //Afficher les meilleurs temps

    printf("Best S1 : %.3f \n", bestS1);

    printf("Best S2 : %.3f \n", bestS2);

    printf("Best S3 : %.3f \n", bestS3);

    printf("Best lap : %.3f \n", bestLap);


}

void simulation(int race_car_number, double race_time, Car drivers[NUMBER_OF_PILOTES],int t_sort) {
    int sem_id;
    int shm_id;
    int reader_num = 1;
    struct sembuf operation = {0};
    Car *circuit;
    key_t key = ftok("..", 666);
    shm_id = shmget(key, 20 * sizeof(struct Car), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("Semget:  semget failed");
        exit(1);
    }
    printf("you entered %d\n", shm_id);
    circuit = (Car *) shmat(shm_id, NULL, 0);
    if (circuit == (Car *) -1) {
        perror("Error while accessing : smat = -1 Direct");
        exit(1);
    }
    sem_id = (int) start_sem();
    printf("Sem started \n");
    //Faire tourner les voitures

    for (int i = 0; i < race_car_number; i++) {
        if (fork() == 0) {
            circuit = shmat(shm_id, NULL, 0);
            if (circuit == (Car *) -1) {
                perror("Erreur shmat = -1 lors du fils");
                exit(1);
            }
            Car *pilote = circuit + i;
            set_total_time_to_zero(pilote);
            change_id((drivers+i)->ID, pilote);
            change_best_lap(999, pilote);
            is_out(0, pilote);
            is_pit(0, pilote);

            while ((pilote)->isOut == 0 && (pilote)->totalTime < race_time) {
                sleep(2);
                change_lap(0, pilote);
                //Si la voiture se crash -> On remet tout les secteurs à zéro et on termine la course
                if (out() == 1) {
                    is_out(1, pilote);
                    change_time_s(0, pilote, 1);
                    change_time_s(0, pilote, 2);
                    change_time_s(0, pilote, 3);
                    exit(0);
                } else {
                    //calcul de S1 + mémoire
                    wait(1, sem_id, operation);
                    change_time_s(sector(), pilote, 1);
                    add_total_time((pilote)->S1, pilote);
                    add_time_lap((pilote)->S1, pilote);
                    post(1, sem_id, operation);
                    //Calcul temps S2 et mise en mémoire
                    wait(1, sem_id, operation);
                    change_time_s(sector(), pilote, 2);
                    add_total_time((pilote)->S2, pilote);
                    add_time_lap((pilote)->S2, pilote);
                    post(1, sem_id, operation);

                    //Calcul pit
                    if (pit() == 1) {
                        is_pit((pilote)->isPit + 1, pilote);
                        usleep(50000);
                        wait(1, sem_id, operation);
                        change_time_s(((double) ramdom(min_pit, max_pit) / (double) 1000) + sector(), pilote, 3);

                        //Ajout du temps dans pit
                        post(i, sem_id, operation);
                    } else {
                        wait(1, sem_id, operation);
                        change_time_s(sector(), pilote, 3);
                        usleep(50000);
                        post(1, sem_id, operation);
                    }
                    wait(1, sem_id, operation);
                    add_time_lap((pilote)->S3, pilote);
                    add_total_time((pilote)->S3, pilote);


                    change_best_lap(min((pilote)->bestLap, (pilote)->lap), pilote);
                    post(1, sem_id, operation);
                    usleep(50000);

                }

            }

            exit(0);
        }
    }
    // Raffraichissement de l'affichage
    for (int compteur = 0; compteur < ((int) race_time / 130 * 3); compteur++) {
        affichage(drivers, race_car_number,circuit,operation,sem_id, reader_num,t_sort);
        usleep(500000);
    }
    if (shmdt(circuit) == -1) {
        perror("Erreur shmdt dans libération de la mémoire");
        exit(1);
    }
    /*if ((shmctl(shm_id,IPC_RMID,NULL)) == -1){
        perror("Erreur de sortie de mémoire");
        exit(1);
    }
    if ((semctl(sem_id,2,IPC_RMID))== -1){
        perror("Erreur de sortie de sémaphore");
        exit(1);
    }*/



}