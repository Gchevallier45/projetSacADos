#ifndef HEURISTIQUE_H_INCLUDED
#define HEURISTIQUE_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "instance.h"

/** Structure contenant une liste chainée d'objets
 */
typedef struct _ListeObjets{
    int objet;          //Numero de l'objet
    struct _ListeObjets *suivant;   //Objet suivant
} ListeObjets;

/** Retourne une liste d'objets initialisée créé sur le tas
 * @return un pointeur sur une liste d'objets
 */
ListeObjets * ListeObjets_initCreer();

/** Vide et détruit une liste d'objets initialisée créé sur le tas
 * @param listeObjets un pointeur sur une structure de type ListeObjets
 */
void ListeObjets_videDetruire(ListeObjets * listeObjets);

void ListeObjets_inserer();

/** Supprime un élément d'un tableau
 * @param tabElem l'adresse d'un tableau de int contenant les objets du sac
 * @param tabTaille la taille du tableau tabElem
 * @param elem l'élément du tableau à supprimer (et non l'indice !)
 * Préconditions : tabElem non nul
 */
void retraitElemTab(int ** tabElem, int tabTaille, int elem);

/** Construit une permutation d'objets
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void randPick(int* tabAlea, Instance instance);



#endif // HEURISTIQUE_H_INCLUDED
