#include "metaheuristique.h"

/** Metaheuristique locale indirecte
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void metaLocalIndirecte(int* tab, Instance instance){
    int *solution = malloc(instance.objetNb*sizeof(int));
    Direct(solution, instance, 3); //On génère la solution de départ

    //Conversion de la solution directe en indirecte
    int *solutionCourante = malloc(0);
    int tailleSolutionCourante = 0;
    for(int i=0; i<instance.objetNb; i++){
        if(solution[i]!=0){
            tailleSolutionCourante++;
            solutionCourante = realloc(solutionCourante, tailleSolutionCourante*sizeof(int));
            solutionCourante[tailleSolutionCourante-1] = i+1;
        }
    }

    int *solutionBest = malloc(tailleSolutionCourante*sizeof(int)); //En codage indirect
    memcpy(solutionBest,solutionCourante,tailleSolutionCourante*sizeof(int));

    memset(solution,0,instance.objetNb*sizeof(int));
    decode(solutionCourante,tailleSolutionCourante,solution,instance);

    affSoluce(solutionCourante,tailleSolutionCourante);
    affSoluce(solution,instance.objetNb);

    free(solution);
    free(solutionCourante);
    free(solutionBest);
}
