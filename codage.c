#include "codage.h"

Solution * Solution_initCreer(){
    Solution * tmp = malloc(sizeof(Solution));
    tmp->objets = NULL;
    tmp->objetNb = 0;
    return tmp;
}

Solution * Solution_videDetruire(Solution *solution){
    free(objets);
    free(solution);
}

Solution * directResultat(int* solutionBinaire, int* valeur, int nbObjets){

    int i;
    Solution * resultat = 0;

    for(i = 0; i < nbObjets; i++){

        resultat = resultat + solutionBinaire[i] * valeur[i];

    }

    //prend en entrée le tableau de la struct et la liste des objets de l'instance
    //permet de donner la valeur des objets du sac

    return resultat;
}


/*  renvoie vrai ou faux si ce qui est dans le sac est une solution possible
    à voir si on se base sur le résultat max de la valeur obtenable du set d'objets
    ou si on compare des capacités et la somme des poids des objets du sac
    dans ses différentes dimensions*/

int directFaisable(int valeurSac, int valeurMax){

    if(valeurSac <= valeurMax)
        return 1;
    else
        return 0;

}


void affSoluce(int solu){


}

void writeSoluce(int solu){


}

Solution * decode(int *permutation, int nbPermutations, Instance* instance){
    int i=0;
    Solution *sac = malloc(sizeof(Solution));
    sac->objetNb = 0;
    sac->objets = NULL;

    instance->objetNb;

    /*while (i!=nbPermutations){
        int j = permutation[i];
        if j peut loger dans le sac then{

        }
        Sac ← Sac ∪ j
        end
        i ← i +1
        end
    }*/

    return sac;
}

