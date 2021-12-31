//
// Created by Loulou on 29/12/2021.
//

#include "../inc/car_stuff.h"
//int ids[20] ={44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};

void change_id(int new_id, Car *voiture){
    voiture -> ID = new_id;
}

void change_time_s(double time_s, Car *voiture, int turn){
    switch (turn) {
        case 1 :
            voiture ->S1 = time_s;
            //printf("S1 changer \n");
        case 2 :
            voiture ->S2 = time_s;
            //printf("S2 changer \n");
        case 3 :
            voiture ->S3 = time_s;
            //printf("S3 changer \n");
    }
}

void change_lap(double time_lap, Car *voiture ){
    voiture -> lap = time_lap;
}
void add_time_lap(double time_lap, Car *voiture ){
    voiture -> lap += time_lap;
}

void change_best_lap(double time_best, Car *voiture ){
    voiture -> bestLap = time_best;
}

void is_out(int is_out, Car *voiture ){
    voiture -> isOut = is_out;
}

void is_pit(int is_pit, Car *voiture ){
    voiture -> isPit = is_pit;
}

void add_total_time(double time_total, Car *voiture ){
    voiture -> totalTime += time_total;
}
void set_total_time_to_zero(Car *voiture){
    voiture->totalTime = (double) 0;
}