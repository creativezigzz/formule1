#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
//
// Created by Loulou on 29/12/2021.
//

#include "../inc/simulation_utils.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int sector_compter = 0;
int min_time = 40000;
int max_time = 50000;

int ramdom(int a, int b){
    srand(time(NULL) * (getpid() *sector_compter));
    return (rand() % (b-a) +a);
}
double sector(){
    if (!sector_compter){

        sector_compter = 0;
    }
    sector_compter++;
    usleep(30000);
    return ((double) ramdom(min_time,max_time) / (double) 1000);
}
int pit(){
    if (ramdom(0, 15) == 1){
        return 1;
    }
    else{
        return 0;
    }
}
int out(){
    if (ramdom(0, 500) == 1) {
        return 1; //Voiture sera out
    } else {
        return 0; //Voiture non out
    }
}
double min(double a, double b){
    if(a > b) return b;
    if (a < b) return a;
    return a;
}


