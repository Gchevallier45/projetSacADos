#include "heuristique.h"

ListeObjets * ListeObjets_initCreer(){
    ListeObjets * tmp = malloc(sizeof(ListeObjets));
    tmp->objet = 0;
    tmp->suivant = NULL;
    return tmp;
}

void ListeObjets_videDetruire(ListeObjets * listeObjets){
    ListeObjets *tmp = listeObjets;
    while(tmp != NULL){
        free(tmp);
        tmp = tmp->suivant;
    }
    free(listeObjets);
}

void retraitElemTab(int ** tabElem, int tabTaille, int elem){
    int indiceElem=0;
    while((*tabElem)[indiceElem]!=elem)
        indiceElem++;

    for(int i = indiceElem; i<tabTaille-1; i++){
        (*tabElem)[i] = (*tabElem)[i+1];
    }

    *tabElem = realloc(*tabElem, sizeof(int)*(tabTaille-1));
}

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
