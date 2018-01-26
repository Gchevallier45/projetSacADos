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

/** Teste si la solution est faisable
 * @param solutionBinaire un tableau de int contenant la solution directe
 * @param instance l'instance correspondant à la solution
 * @return 1 si la solution est faisable, 0 sinon
 */
int directFaisable(int* solutionBinaire, Instance *instance){
    int dimensionNb = instance->dimensionNb;
    int *sommePoids = calloc(dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension
    for(int i=0; i<instance->objetNb; i++){
        if(solutionBinaire[i] == 1){
            for(int j=0; j<dimensionNb; j++){
                sommePoids[j]+=instance->Rij[j][i]; //Par défaut on considère que l'objet rentre dans le sac (permet de gagner un peu de temps)
                if(sommePoids[j] > instance->Bi[j]){ //Si ce n'est pas le cas on l'enlève du sac
                    free(sommePoids);
                    return 0;
                }
            }
        }
    }
    free(sommePoids);
    return 1;
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
 * @param solution un tableau de int contenant une solution
 * @param nbObjets la taille du tableau de la solution
 */
void writeSoluce(int* solution, int nbObjets){
    FILE * fichier = NULL;
    fichier = fopen("sortie.txt","a");

    if(fichier == NULL){
        printf("Problème pour écrire la valeur dans sortie.txt");
        exit(0);
    }

    //fprintf(fichier," %d\n",solu);
    fprintf(fichier,"|");
    for(int i=0;i<nbObjets;i++)
        fprintf(fichier,"%d|",solution[i]);
    fprintf(fichier,"\n");
    fclose(fichier);
}

/** Décode une solution indirecte en solution directe
 * @param permutation un tableau de int contenant une permutation d'objets
 * @param solution le tableau dans lequel stocker la solution directe
 * @param instance l'instance correspondant à la permutation
 */
void decode(int *permutation, int *solution, Instance *instance){
    int nbPermutations = instance->objetNb;
    int dimensionNb = instance->dimensionNb;
    int *sommePoids = calloc(dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension
    int *endpermut = permutation + nbPermutations;
    int *zeros = calloc(instance->objetNb,sizeof(int));

    if(*permutation <= 0 || *permutation >= instance->objetNb){ //Si la permutation est incorrecte on renvoie une solution vide
        memcpy(solution,zeros,instance->objetNb*sizeof(int));
    }
    else{
        while(permutation < endpermut){
            int j;
            for(j=0; j<dimensionNb; j++){
                sommePoids[j]+=instance->Rij[j][*permutation-1]; //Par défaut on considère que l'objet rentre dans le sac (permet de gagner un peu de temps)
                if(sommePoids[j] > instance->Bi[j]){ //Si ce n'est pas le cas on l'enlève du sac
                    for(int k=0; k<=j; k++){
                        sommePoids[k]-=instance->Rij[k][*permutation-1];
                    }
                    break;
                }
            }

            //Si l'objet rentre dans toutes les dimensions on met la case de l'objet à 1 dans la solution directe
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
    }
    free(sommePoids);
    free(zeros);
}

