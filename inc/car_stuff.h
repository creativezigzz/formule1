//
// Created by Loulou on 29/12/2021.
//

#ifndef FORMULE1_CAR_STUFF_H
#define FORMULE1_CAR_STUFF_H
//Structure
typedef struct Car {
    int ID; //ID du pilote
    double S1; //Temps S1
    double S2; //Temps S2
    double S3; //Temps S3
    double lap; //Temps tour = somme des temps
    double bestLap; //Temps meilleur tour
    int isOut; //Statut de out ou non (0=non, 1=oui)
    int isPit; //Nombre de passage en pit
    double totalTime; //Temps total de la course de cette voiture
} Car;
//API CAR
extern void assign_car(Car *voiture);

extern void change_id(int new_id, Car *voiture);

extern void change_time_s(double time_s, Car *voiture, int turn);

extern void change_lap(double time_lap, Car *voiture);

extern void change_best_lap(double time_best, Car *voiture);

extern void is_out(int is_out, Car *voiture);

extern void is_pit(int is_pit, Car *voiture);

extern void add_total_time(double time_total, Car *voiture);
extern void set_total_time_to_zero(Car *voiture);
extern void add_time_lap(double time_lap, Car *voiture);
//Variables globales pour Car
int ids[20];
#define NUMBER_OF_PILOTES 20
#endif //FORMULE1_CAR_STUFF_H
