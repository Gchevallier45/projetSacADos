#ifndef HEURISTIQUE_H_INCLUDED
#define HEURISTIQUE_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "instance.h"

/** Supprime un élément d'un tableau
 * @param tabElem l'adresse d'un tableau de int contenant les objets du sac
 * @param tabTaille la taille du tableau tabElem
 * @param elem l'élément du tableau à supprimer (et non l'indice !)
 * Préconditions : tabElem non nul
 */
void retraitElemTab(int ** tabElem, int tabTaille, int elem);

/** Remplit un tableau avec une permutation d'objets aléatoire
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void randPick(int* tabAlea, Instance *instance);

/** Remplit un tableau avec une permutation d'objets de valeur décroissante
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decValPick(int* tab, Instance *instance);

/** Remplit un tableau avec une permutation d'objets avec un ratio valeur/sommedespoids décroissant
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decRatioValPoidsPick(int* tab, Instance *instance);

/** Remplit un tableau avec une permutation d'objets avec un ratio valeur/sommedespoids sur la dimension critique décroissant
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decRatioValPoidsCritPick(int* tab, int tailleTab, Instance *instance, int *etatDimensions);

/** Heuristique indirecte
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void Indirect(int* tab, Instance *instance, int typeOrdonnancement);

/** Heuristique directe
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void Direct(int* tab, Instance *instance, int typeOrdonnancement);



#endif // HEURISTIQUE_H_INCLUDED
