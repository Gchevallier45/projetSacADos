#include "heuristique.h"

/** Retourne une liste d'objets initialisée créé sur le tas
 * @return un pointeur sur une liste d'objets
 */
ListeObjets * ListeObjets_initCreer(){
    ListeObjets * tmp = malloc(sizeof(ListeObjets));
    tmp->objet = 0;
    tmp->suivant = NULL;
    return tmp;
}

/** Vide et détruit une liste d'objets initialisée créé sur le tas
 * @param listeObjets un pointeur sur une structure de type ListeObjets
 */
void ListeObjets_videDetruire(ListeObjets * listeObjets){
    ListeObjets *tmp = listeObjets;
    while(tmp != NULL){
        free(tmp);
        tmp = tmp->suivant;
    }
    free(listeObjets);
}

/** Supprime un élément d'un tableau
 * @param tabElem l'adresse d'un tableau de int contenant les objets du sac
 * @param tabTaille la taille du tableau tabElem
 * @param elem l'élément du tableau à supprimer (et non l'indice !)
 * Préconditions : tabElem non nul
 */
void retraitElemTab(int ** tabElem, int tabTaille, int elem){
    int indiceElem=0;
    while((*tabElem)[indiceElem]!=elem)
        indiceElem++;

    for(int i = indiceElem; i<tabTaille-1; i++){
        (*tabElem)[i] = (*tabElem)[i+1];
    }

    *tabElem = realloc(*tabElem, sizeof(int)*(tabTaille-1));
}

/** Construit une permutation d'objets
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void randPick(int* tabAlea, Instance instance){
    srand(time(NULL));

    int * intermediaire = (int*)malloc( (instance.objetNb) * sizeof(int));
    for(int i=0; i < instance.objetNb; i++){
        intermediaire[i] = i;
    }

    for(int i=0; i < instance.objetNb; i++){
        tabAlea[i] = intermediaire[rand() % (instance.objetNb - (i))];
        retraitElemTab(&intermediaire,instance.objetNb-(i),tabAlea[i]);
    }
}
