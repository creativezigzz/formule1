//
// Created by Loulou on 29/12/2021.
//

#ifndef FORMULE1_SIMULATION_H
#define FORMULE1_SIMULATION_H

#include "car_stuff.h"
#include <sys/types.h>
#include <sys/sem.h>
void simulation(int race_car_number, double race_time, Car drivers[NUMBER_OF_PILOTES],int t_sort);

int start_sem();

void wait(int i, int this_sem_id,struct sembuf);

void post(int i, int this_sem_ids,struct sembuf);

void begin_reading(int this_sem_id, struct sembuf op,int nbr_reader);

void stop_reading(int this_sem_id, struct sembuf op, int nbr_reader);

void sort(Car drivers[NUMBER_OF_PILOTES], Car *circuit,int race_car_number,struct sembuf operation,int new_sem_id, int nbr_reader);
void sort_by_total(Car drivers[NUMBER_OF_PILOTES], Car *circuit,int race_car_number,struct sembuf operation,int new_sem_id, int nbr_reader);
void affichage(Car drivers[NUMBER_OF_PILOTES],int race_car_number, Car * circuit, struct sembuf op,int new_sem_id,int nbr_reader, int t_sort);


int min_pit;
int max_pit;

#endif //FORMULE1_SIMULATION_H
