#ifndef HEURISTIQUE_H_INCLUDED
#define HEURISTIQUE_H_INCLUDED

typedef struct _ListeObjets{
    int objet;
    struct _ListeObjet *suivant;
} ListeObjets;

ListeObjets * ListeObjets_initCreer();
ListeObjets * ListeObjets_videDetruire(ListeObjets * listeObjets);

#endif // HEURISTIQUE_H_INCLUDED
