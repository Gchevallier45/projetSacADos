#ifndef CODAGE_H_INCLUDED
#define CODAGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instance.h"

/*typedef struct _Solution{
    int *objets;
    int objetNb;
} Solution;*/

typedef struct _codageDirect{

    int* sac;       //vecteur de booléens qui indique si un objet est mis dans le sac ou non
    int resultat;   //somme des valeurs
    int faisabilite;//


}codageDirect;

/*Solution * Solution_initCreer();
Solution * Solution_videDetruire(Solution *solution);*/


int directResultat(int* sac, int* valeur, int nbObjets);

#endif // CODAGE_H_INCLUDED
