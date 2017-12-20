#include "codage.h"


int directResultat(int* sac, int* objet, int nbObjets){

    int i;
    int resultat = 0;

    for(i = 0; i < nbObjets; i++){

        resultat = resultat + sac[i] * objet[i];

    }

    //prend en entrée le tableau de la struct et la liste des objets de l'instance
    //permet de donner la valeur des objets du sac

    return resultat;
}


/*  renvoie vrai ou faux si ce qui est dans le sac est une solution possible
    à voir si on se base sur le résultat max de la valeur obtenable du set d'objets
    ou si on compare des capacités et la somme des poids des objets du sac
    dans ses différentes dimensions*/

int directFaisable(int* tab){

    return 1;
}


void affSoluce(int solu){


}

void writeSoluce(int solu){


}


