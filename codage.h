#ifndef CODAGE_H_INCLUDED
#define CODAGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instance.h"

/** Affiche la valeur d'une solution directe
 * @param solutionBinaire un tableau de int contenant la solution directe
 * @param instance l'instance correspondant à la solution
 * @return la valeur de la solution
 */
int directResultat(int *solutionBinaire, Instance *instance);

/** Teste si la solution est faisable
 * @param solutionBinaire un tableau de int contenant la solution directe
 * @param instance l'instance correspondant à la solution
 * @return 1 si la solution est faisable, 0 sinon
 */
int directFaisable(int* solutionBinaire, Instance *instance);

/** Affiche une solution
 * @param solution un tableau de int contenant une solution
 * @param nbObjets la taille du tableau de la solution
 */
void affSoluce(int* solution, int nbObjets);

/** Ecrit une solution dans un fichier de sortir
 * @param solu la valeur de la solution à écrire
 */
void writeSoluce(int solu);

/** Décode une solution indirecte en solution directe
 * @param permutation un tableau de int contenant une permutation d'objets
 * @param solution le tableau dans lequel stocker la solution directe
 * @param instance l'instance correspondant à la permutation
 */
void decode(int *permutation, int *solution, Instance *instance);

#endif // CODAGE_H_INCLUDED
