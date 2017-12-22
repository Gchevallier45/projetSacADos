#ifndef HEURISTIQUE_H_INCLUDED
#define HEURISTIQUE_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "instance.h"
//liste chainée d'oobjets
typedef struct _ListeObjets{
    int objet;          //Numero de l'objet
    struct _ListeObjets *suivant;   //Objet suivant
} ListeObjets;

ListeObjets * ListeObjets_initCreer();
void ListeObjets_videDetruire(ListeObjets * listeObjets);
void ListeObjets_inserer();



#endif // HEURISTIQUE_H_INCLUDED
