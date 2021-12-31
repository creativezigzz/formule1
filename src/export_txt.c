//
// Created by Loulou on 29/12/2021.
//

#include "../inc/export_txt.h"
#include <stdlib.h>
#include <stdio.h>
int export_txt(int step, int nbr_voiture, Car drivers[NUMBER_OF_PILOTES]) {
    FILE *fichier = NULL;
    //Pour définir les noms des fichiers
    switch (step) {
        case 1 :
            fichier = fopen("../file/Essai1.txt", "w+");
//printf("Ecriture essai 1");
            break;
        case 2 :
            fichier = fopen("../file/Essai2.txt", "w+");
//printf("Ecriture essai 2");
            break;
        case 3 :
            fichier = fopen("../file/Essai3.txt", "w+");
//printf("Ecriture essai 3");
            break;
        case 4 :
            fichier = fopen("../file/Qualif1.txt", "w+");
//printf("Ecriture qualif 1");
            break;
        case 5 :
            fichier = fopen("../file/Qualif2.txt", "w+");
//printf("Ecriture qualif 2");
            break;
        case 6 :
            fichier = fopen("../file/Qualif3.txt", "w+");
//printf("Ecriture qualif 3");
            break;
        case 7 :
            fichier = fopen("../file/Course.txt", "w+");
//printf("Ecriture course");
            break;
        default:
            printf("Erreur de nom de fichier, il n'est pas dans la course \n");
    }
    if (fichier != NULL) {
//Début de l'écriture
        fprintf(fichier, "|N°\t|S1\t\t|S2\t\t|S3\t\t|Tour\t\t|Best\t\t|PIT\t|OUT\t|\n");
        fprintf(fichier, "\n");
        for (int j = 0; j < nbr_voiture; j++) {
            Car *pilote = drivers + j;

            fprintf(fichier, "|%d\t", (pilote)->ID); //Imprime le N°
            if (pilote->S1 == 0) { //Imprime le temps S1

                fprintf(fichier, "|NULL\t");
            } else {
                fprintf(fichier, "|%.3f\t", (pilote)->S1);
            }
            if ((pilote)->S2 == 0) { //Imprime le temps S2
                fprintf(fichier, "|NULL\t");
            } else {
                fprintf(fichier, "|%.3f\t", (pilote)->S2);
            }
            if ((pilote)->S3 == 0) { //Imprime le temps S3
                fprintf(fichier, "|NULL\t");
            } else {
                fprintf(fichier, "|%.3f\t",(pilote)->S3);
            }
            if ((pilote)->lap == 0) { //Imprime le temps du tour
                fprintf(fichier, "|NULL\t\t");
            } else if ((pilote)->lap < 100.000) {
                fprintf(fichier, "|%.3f\t\t", (pilote)->lap);
            } else {
                fprintf(fichier, "|%.3f\t", (pilote)->lap);
            }
            if ((pilote)->bestLap < 100.000) { //Imprime le meilleur temps
                fprintf(fichier, "|%.3f\t\t", (pilote)->bestLap);
            } else {
                fprintf(fichier, "|%.3f\t", (pilote)->bestLap);
            }
            if ((pilote)->isPit != 0) { //Imprime le nombre de pit du pilote
                fprintf(fichier, "|%d\t", (pilote)->isPit);
            } else {
                fprintf(fichier, "|0\t");
            }
            if ((pilote)->isOut == 1) { //Imprime si le pilote est out
                fprintf(fichier, "|X\t|\n");
            } else {
                fprintf(fichier, "|\t|\n");
            }


        }//Fin ecriture
        if (step == 7){
            fprintf(fichier,"Best lap is %.3f \n", drivers[0].bestLap);
        }
        fclose(fichier);

    }
    return 0;
}