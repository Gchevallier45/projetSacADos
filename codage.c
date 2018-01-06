#include "codage.h"

/** Affiche la valeur d'une solution directe
 * @param solutionBinaire un tableau de int contenant la solution directe
 * @param instance l'instance correspondant à la solution
 * @return la valeur de la solution
 */
int directResultat(int* solutionBinaire, Instance *instance){
    int* valeur = instance->Pj;
    int resultat = 0;

    for(int i = 0; i < instance->objetNb; i++){
        resultat = resultat + *solutionBinaire * *valeur;
        solutionBinaire++;
        valeur++;
    }

    return resultat;
}

/** Renvoie 1 si la solution est faisable, 0 sinon
 * @param
 * @param
 */
int directFaisable(int valeurSac, int valeurMax){
    return(valeurSac <= valeurMax);
}

/** Affiche une solution
 * @param solution un tableau de int contenant une solution
 * @param nbObjets la taille du tableau de la solution
 */
void affSoluce(int* solution, int nbObjets){
    printf("|");
    for(int i=0;i<nbObjets;i++)
        printf("%d|",solution[i]);
    printf("\n");
}

/** Ecrit une solution dans un fichier de sortir
 * @param solu la valeur de la solution à écrire
 */
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

/** Décode une solution indirecte en solution directe
 * @param permutation un tableau de int contenant une permutation d'objets
 * @param nbPermutations la taille du tableau de permutations
 * @param solution le tableau dans lequel stocker la solution directe
 * @param instance l'instance correspondant à la permutation
 */
void decode(int *permutation, int nbPermutations, int *solution, Instance *instance){
    int dimensionNb = instance->dimensionNb;
    int *sommePoids = calloc(dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension
    int *endpermut = permutation + nbPermutations;

    while(permutation < endpermut){
        /*int resultTest = 0;

        for(int j=0; j<dimensionNb; j++){
            if(sommePoids[j]+instance->Rij[j][*permutation-1] < instance->Bi[j]){
                resultTest++;
            }
            else{
                break;
            }
        }

        if(resultTest == dimensionNb){
            for(int j=0; j<dimensionNb; j++){
                sommePoids[j]+=instance->Rij[j][*permutation-1];
            }
            solution[*permutation-1] = 1;
        }*/

        int j;
        for(j=0; j<dimensionNb; j++){
            sommePoids[j]+=instance->Rij[j][*permutation-1];
            if(sommePoids[j] > instance->Bi[j]){
                for(int k=0; k<=j; k++){
                    sommePoids[k]-=instance->Rij[k][*permutation-1];
                }
                break;
            }
        }

        if(j == dimensionNb){
            solution[*permutation-1] = 1;
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

