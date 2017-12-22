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

int * randPick(Instance * instance){

    int* intermediaire;
    int* tabAlea;
    int i;

    intermediaire = (int*)malloc( (instance->objetNb) * sizeof(int));
    tabAlea = (int*)malloc( (instance->objetNb) * sizeof(int));
    for(i=0; i < instance->objetNb; i++){
        intermediaire[i] = i;
    }

    for(i = 0; i < instance->objetNb; i++){
        tabAlea[i] = intermediaire[rand() % (instance->objetNb - i)];
        retraitElemTab(&intermediaire,instance->objetNb-i,tabAlea[i]);

    }

    return tabAlea;
}


void retraitElemTab(int ** tabElem, int tabTaille, int indiceElem){

    int i;
    for(i = indiceElem; i<tabTaille; i++)
        *tabElem[i] = *tabElem[i+1];

    realloc(*tabElem, sizeof(int)*(tabTaille - 1));

    return tabElem;
}
