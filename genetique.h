#ifndef GENETIQUE_H_INCLUDED
#define GENETIQUE_H_INCLUDED

#include "heuristique.h"
#define DIRECT 0
#define INDIRECT 1


typedef struct _Population{
    int **solutions;
    int taillePopu;
    int type;
} Population;

void initPopulation(Population *population, int taillePopulation, int typeSolutions, Instance *instance);

void detruirePopulation(Population *population);


#endif // GENETIQUE_H_INCLUDED
