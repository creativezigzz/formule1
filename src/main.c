#include "../inc/simulation.h"
#include "../inc/export_txt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int lap_time = 130;
int total_lap = 45;
int ids[20] ={44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};
int main() {
    Car tri[NUMBER_OF_PILOTES];

    for(int i = 0; i < 20; i++){
        Car *tri_ptr = tri + i;
        change_id(ids[i],tri_ptr);
        printf("Ici id n° %d \n",tri_ptr->ID);

    }

    sleep(1);
    simulation(20, 5400, tri,0);
    export_txt(1, 20, tri);
    sleep(2);
    system("clear");
    //Essai 2
//printf("\t\nEssai2");
    sleep(1);
    simulation(20, 5400, tri,0);
    export_txt(2, 20, tri);
    sleep(2);
    system("clear");
    //Essai 3
//printf("\t\nEssai3");
    sleep(1);
    simulation(20, 3600, tri,0);
    export_txt(3, 20, tri);
    sleep(2);
    system("clear");
    //Qualif 1 toutes les voitures

    sleep(1);
    simulation(20, 1080, tri,0);
    export_txt(4, 20, tri);
    sleep(2);
    system("clear");
    //Qualif 2 les 15 premières voitures

    sleep(1);
    simulation(15, 900, tri,0);
    export_txt(5, 15, tri);
    sleep(2);
    system("clear");
    //Qualif 3 les 10 premières voitures

    sleep(1);
    simulation(10, 720, tri,0);
    export_txt(6, 10, tri);
    sleep(2);
    system("clear");
    //Course
    sleep(1);
    simulation(20, lap_time*total_lap, tri,1);
    export_txt(7, 20, tri);
    sleep(2);
    system("clear");
}
