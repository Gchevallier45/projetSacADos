#include "codage.h"


typedef struct _codageDirect{

    int* sac;
    int resultat;
    int faisabilite;


}codageDirect;

int directResultat(int* tab, int* objet){

    //prend en entrée le tableau de la struct et la liste des objets de l'instance
    //permet de donner la valeur des objets du sac

    return 1;
}

int directFaisable(int* tab){

    return 1;
}


void affSoluce(int solu){


}

void writeSoluce(int solu){


}

Sac * decode(int *permutation, int nbPermutations){
    int i=0;
    Sac *sac = malloc(sizeof(Sac));
    sac->objetNb = 0;
    sac->objets = NULL;

    while (i!=nbPermutations){
        int j = permutation[i];
        if j peut loger dans le sac then{

        }
        Sac ← Sac ∪ j
        end
        i ← i +1
        end
    }

    return sac;
}

