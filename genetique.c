#include "genetique.h"

void initPopulation(Population *population, int taillePopulation, int typeSolutions, Instance *instance){
    population->taillePopu = taillePopulation;
    population->type = typeSolutions;
    population->solutions = (int*)malloc(taillePopulation*sizeof(int*));
    if(typeSolutions == DIRECT){
        for(int i=0;i<taillePopulation;i++){
            int *solution = malloc(instance->objetNb*sizeof(int));
            Direct(solution,instance,1);
            population->solutions[i] = solution;
        }
    }
    else{
        for(int i=0;i<taillePopulation;i++){
            int *solution = malloc(instance->objetNb*sizeof(int));
            decRatioValPoidsPick(solution, instance);
            population->solutions[i] = solution;
        }
    }
}

void detruirePopulation(Population *population){
    for(int i=0;i<population->taillePopu;i++){
        free(population->solutions[i]);
    }
    free(population->solutions);
    free(population);
}

/** Metaheuristique génétique
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaGenetiqueDirecte(int* tab, Instance *instance, int nbIteMax, int taillePopu, int pMut){
    Population *pop = malloc(sizeof(Population));
    initPopulation(pop,taillePopu,DIRECT,instance);
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int valMeilleureSolution = 0;
    int indiceMeilleureSolution = 0;
    for(int i=0;i<pop->taillePopu;i++){
        int val = directResultat(pop->solutions[i],instance);
        if(val > valMeilleureSolution){
            valMeilleureSolution = val;
            indiceMeilleureSolution = i;
        }
    }

    //memcpy(tab,pop->solutions[indiceMeilleureSolution],instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    detruirePopulation(pop);

}
