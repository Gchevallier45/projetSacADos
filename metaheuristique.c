#include "metaheuristique.h"

/** Metaheuristique locale indirecte
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaLocalIndirecte(int* tab, Instance *instance){
    int *solutionCourante = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solutionVoisine = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solutionBestVoisine = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solution = calloc(instance->objetNb,sizeof(int)); //En codage direct

    decRatioValPoidsPick(solutionCourante, instance); //On génère la solution de départ avec l'algo d'ordonnancement le + performant
    memcpy(solutionBest,solutionCourante,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest
    memcpy(solutionBestVoisine,solutionCourante,instance->objetNb*sizeof(int));

    //Calcul de fbest
    decode(solutionCourante,instance->objetNb,solution,instance);
    int fbest = directResultat(solution,instance);
    int continuer = 1;
    int fcourant = fbest;
    int fprec = fcourant;

    while(continuer == 1){
        memcpy(solutionVoisine,solutionCourante,instance->objetNb*sizeof(int));
        int fbestvoisin = 0;
        for(int i=0;i<instance->objetNb/2;i++){
            for(int j=i+1;j<instance->objetNb;j++){ //j=i+1 car les permutations de 0 à i+1 ont déjà été effectuées dans les itérations d'avant
                //Permutation des éléments
                int tmp = solutionVoisine[i];
                solutionVoisine[i] = solutionVoisine[j];
                solutionVoisine[j] = tmp;

                //Décodage et évaluation de la solution voisine
                memset(solution,0,instance->objetNb*sizeof(int));
                decode(solutionVoisine,instance->objetNb,solution,instance);
                int resultat=directResultat(solution,instance);
                if(resultat > fbestvoisin){
                    memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                    fbestvoisin = resultat;
                }

                //Dépermutation des éléments pour restaurer la solutionCourante
                tmp = solutionVoisine[i];
                solutionVoisine[i] = solutionVoisine[j];
                solutionVoisine[j] = tmp;
            }
        }
        fcourant = fbestvoisin;
        memcpy(solutionCourante,solutionBestVoisine,instance->objetNb*sizeof(int));
        if(fcourant>fbest){
            fbest=fcourant;
            memcpy(solutionBest,solutionCourante,instance->objetNb*sizeof(int));
        }
        else if(fcourant<=fprec){
            continuer = 0;
        }
        fprec = fcourant;
    }

    //Copie de la solution dans le tableau de destination
    memset(solution,0,instance->objetNb*sizeof(int));
    decode(solutionBest,instance->objetNb,solution,instance);
    memcpy(tab,solution,instance->objetNb*sizeof(int));

    free(solution);
    free(solutionCourante);
    free(solutionBest);
    free(solutionVoisine);
    free(solutionBestVoisine);
}
