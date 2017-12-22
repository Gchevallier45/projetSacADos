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

