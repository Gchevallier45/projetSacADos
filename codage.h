#ifndef CODAGE_H_INCLUDED
#define CODAGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Sac{
    int *objets;
    int objetNb;
} Sac;

typedef struct _codageDirect{

    int* sac;       //vecteur de booléens qui indique si un objet est mis dans le sac ou non
    int resultat;   //somme des valeurs
    int faisabilite;//


}codageDirect;

#endif // CODAGE_H_INCLUDED
