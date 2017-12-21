#include "codage.h"

int directResultat(int* solutionBinaire, int* valeur, int nbObjets){

    int i;
    int resultat = 0;

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

    printf("la valeur de la solution est : %d", solu);
}

void writeSoluce(int solu){

    FILE * fichier;

    fopen("sortie.txt","a");
}

int decode(int *permutation, int nbPermutations, Instance* instance){
    int i=0;
    //int *sac = malloc(sizeof(Solution));
    //sac->objetNb = 0;
    //sac->objets = NULL;

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

    return 0;
}

