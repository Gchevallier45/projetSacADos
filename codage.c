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

    FILE * fichier = NULL;

    fichier = fopen("sortie.txt","a");

    if(fichier == NULL){
        printf("Problème pour écrire la valeur dans sortie.txt");
        exit(0);
    }

    fprintf(fichier," %d\n",solu);

    fclose(fichier);
}

void decode(int *permutation, int nbPermutations, int *solution, Instance instance){
    int *sommePoids = calloc(instance.dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension

    /*for(int i=0; i<nbPermutations;i++){
        int resultTest = 0;

        for(int j=0; j<instance.dimensionNb; j++){
            if(sommePoids[j]+instance.Rij[j][permutation[i]] < instance.Bi[j])
                resultTest++;
        }

        if(resultTest == instance.dimensionNb){
            for(int j=0; j<instance.dimensionNb; j++){
                sommePoids[j]+=instance.Rij[j][permutation[i]];
            }
            solution[permutation[i]] = 1;
        }

        /*printf("\n");
        printf("Solution 0 : %d, Max poids dim : %d\n", sommePoids[0], instance.Bi[0]);
        printf("Solution 1 : %d, Max poids dim : %d\n", sommePoids[1], instance.Bi[1]);
        printf("Solution 2 : %d, Max poids dim : %d\n", sommePoids[2], instance.Bi[2]);
        printf("Solution 3 : %d, Max poids dim : %d\n", sommePoids[3], instance.Bi[3]);
        printf("Solution 4 : %d, Max poids dim : %d\n", sommePoids[4], instance.Bi[4]);
        printf("---------------------------------------------");*/
    //}

    int *endpermut = permutation + nbPermutations;
    while(permutation < endpermut){
        int resultTest = 0;

        for(int j=0; j<instance.dimensionNb; j++){
            if(sommePoids[j]+instance.Rij[j][*permutation] < instance.Bi[j]){
                resultTest++;
            }
            else{
                break;
            }
        }

        if(resultTest == instance.dimensionNb){
            for(int j=0; j<instance.dimensionNb; j++){
                sommePoids[j]+=instance.Rij[j][*permutation];
            }
            solution[*permutation] = 1;
        }

        /*printf("\n");
        printf("Solution 0 : %d, Max poids dim : %d\n", sommePoids[0], instance.Bi[0]);
        printf("Solution 1 : %d, Max poids dim : %d\n", sommePoids[1], instance.Bi[1]);
        printf("Solution 2 : %d, Max poids dim : %d\n", sommePoids[2], instance.Bi[2]);
        printf("Solution 3 : %d, Max poids dim : %d\n", sommePoids[3], instance.Bi[3]);
        printf("Solution 4 : %d, Max poids dim : %d\n", sommePoids[4], instance.Bi[4]);
        printf("---------------------------------------------");*/
        permutation++;
    }
    free(sommePoids);
}

