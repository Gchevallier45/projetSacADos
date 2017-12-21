#include "heuristique.h"

ListeObjets * ListeObjets_initCreer(){
    ListeObjets * tmp = malloc(sizeof(ListeObjets));
    tmp->objet = 0;
    tmp->suivant = NULL;
    return tmp;
}

ListeObjets * ListeObjets_videDetruire(ListeObjets * listeObjets){
    //for(int i=0;i<listeObjets->objet)
}
