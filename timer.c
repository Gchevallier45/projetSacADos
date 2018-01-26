#include "timer.h"

/** Ecrit le résultat du calcul dans un fichier de sortie
 * @param noInstance le numéro d'instance utilisé lors du calcul
 * @param valeurSolution la fonction objectif de la meilleure solution trouvée pour cette instance
 * @param temps le temps de calcul pris par l'algorithme de résolution
 */
void timeFile(int noInstance, int valeurSolution, double temps){

    FILE* sortie = NULL;

    if(noInstance != 1){
        sortie = fopen("sortie.txt","a");
    }else {
        sortie = fopen("sortie.txt","w+");
        fprintf(sortie,"INSTANCE | SOLUTION | TEMPS CALCUL |\n");
    }

    if(sortie == NULL){
        printf("Problème pour écrire le temps dans sortie.txt");
        exit(0);
    }

    fprintf(sortie,"   %.2d    |  %d   |   %f   |\n", noInstance, valeurSolution, temps);
    fclose(sortie);

}

/** Démarre un timer
 * @return retourne une valeur de référence pour calculer le temps écoulé
 */
time_t timer_start(){
    return clock();
}

/** Démarre un timer
 * @param timer la valeur de référence du timer
 * @return retourne la différence entre le temps actuel et la valeur de référence passée en paramètre
 */
double timer_getTime(time_t timer){

    double timeElapsed;
    timeElapsed = (clock()-timer)/(double)CLOCKS_PER_SEC;

    return timeElapsed;
}
