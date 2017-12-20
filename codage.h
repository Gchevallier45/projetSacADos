#ifndef CODAGE_H_INCLUDED
#define CODAGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instance.h"

typedef struct _Sac{
    int *objets;
    int objetNb;
} Sac;

typedef struct _codageDirect{

    int* sac;
    int resultat;
    int faisabilite;


}codageDirect;

#endif // CODAGE_H_INCLUDED
