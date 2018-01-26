#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Ecrit le résultat du calcul dans un fichier de sortie
 * @param noInstance le numéro d'instance utilisé lors du calcul
 * @param valeurSolution la fonction objectif de la meilleure solution trouvée pour cette instance
 * @param temps le temps de calcul pris par l'algorithme de résolution
 */
void timeFile(int noInstance, int valeurSolution, double temps);

/** Démarre un timer
 * @return retourne une valeur de référence pour calculer le temps écoulé
 */
time_t timer_start();

/** Démarre un timer
 * @param timer la valeur de référence du timer
 * @return retourne la différence entre le temps actuel et la valeur de référence passée en paramètre
 */
double timer_getTime(time_t timer);


#endif // TIMER_H_INCLUDED
