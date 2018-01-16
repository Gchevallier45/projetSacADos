#include "genetique.h"

void initPopulation(Population *population, int taillePopulation, int typeSolutions){
    population->taillePopu = taillePopulation;
    population->type = typeSolutions;
    population->solutions = (int*)malloc(taillePopulation*sizeof(int*));
}

void creerPopulation(Population *population, int taillePopulation, int typeSolutions, Instance *instance){
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
    creerPopulation(pop,taillePopu,DIRECT,instance);
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int valSolutionBest = 0;
    int indiceSolutionBest  = 0;
    for(int i=0;i<pop->taillePopu;i++){
        int val = directResultat(pop->solutions[i],instance);
        if(val > valSolutionBest){
            valSolutionBest = val;
            indiceSolutionBest = i;
        }
    }

    memcpy(solutionBest,pop->solutions[indiceSolutionBest],instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    int nbIte = 0;
    while(nbIte < nbIteMax){
        Population *enfant = malloc(sizeof(Population));
        initPopulation(enfant,taillePopu,DIRECT);

        for(int i=0;i<taillePopu/2;i++){
            int parents[2];

            //On séléctionne des parents aléatoires
            parents[0] = rand() % taillePopu;
            parents[1] = rand() % taillePopu;
            while(parents[0] == parents[1]){
                parents[1] = rand() % taillePopu;
            }

            //On créée des enfants
            int pointCroisement = rand() % instance->objetNb;
            int *enfant1 = malloc(instance->objetNb*sizeof(int));
            int *enfant2 = malloc(instance->objetNb*sizeof(int));

            int *parent1 = pop->solutions[parents[0]];
            int *parent2 = pop->solutions[parents[1]];
            int p=0;
            while(parent1<(parent1+instance->objetNb)){
                printf("%d\n",p);
                p++;
                parent1++;
            }
            memcpy(enfant1,pop->solutions[parents[0]],pointCroisement);
            memcpy(enfant1+pointCroisement,pop->solutions[parents[0]]+pointCroisement,instance->objetNb-pointCroisement);
            printf("-----------\n");
            affSoluce(pop->solutions[parents[0]],instance->objetNb);
            affSoluce(enfant1,instance->objetNb);
            printf("point crois %d, deux copie %d, total %d\n\n",pointCroisement,instance->objetNb-pointCroisement,instance->objetNb-pointCroisement+pointCroisement);

            //printf("PARENT 1 : %d, PARENT 2 : %d\n",parents[0],parents[1]);
        }
        nbIte++;
    }

    memcpy(tab,pop->solutions[indiceSolutionBest],instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    detruirePopulation(pop);
    free(solutionBest);
}
