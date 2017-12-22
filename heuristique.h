#ifndef HEURISTIQUE_H_INCLUDED
#define HEURISTIQUE_H_INCLUDED

#include <stdlib.h>

typedef struct _ListeObjets{
    int objet;
    struct _ListeObjets *suivant;
} ListeObjets;

ListeObjets * ListeObjets_initCreer();
void ListeObjets_videDetruire(ListeObjets * listeObjets);
void ListeObjets_inserer();



#endif // HEURISTIQUE_H_INCLUDED
