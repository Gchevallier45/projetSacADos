#include "timer.h"

void timeFile(double temps){

    static int nbInstance = 0;
    FILE* sortie = NULL;

    if(nbInstance != 0){
        sortie = fopen("sortie.txt","a");
        nbInstance++;
    }else {
        sortie = fopen("sortie.txt","w+");
        nbInstance = 1;
    }

    if(sortie == NULL){
        printf("Problème pour écrire dans sortie.txt");
        exit(0);
    }

    fprintf(sortie,"Temps Instance %d : %lf s\n", nbInstance, temps);

    fclose(sortie);

}

time_t timer_start(){
    return clock();
}

double timer_getTime(time_t timer){

    double timeElapsed;
    timeElapsed = (clock()-timer)/(double)CLOCKS_PER_SEC;
    timeFile(timeElapsed);
    return timeElapsed;
}
