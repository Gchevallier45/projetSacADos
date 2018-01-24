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

/** Metaheuristique génétique direct
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param taillePopu la taille de la population à utiliser
 * @param pMut la probabilité de mutation d'un enfant
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaGenetiqueDirecte(int* tab, Instance *instance, int nbIteMax, int taillePopu, int pMut){
    Population *pop = malloc(sizeof(Population));
    creerPopulation(pop,taillePopu,DIRECT,instance);
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int fbest = 0;
    int indiceSolutionBest  = 0;
    for(int i=0;i<pop->taillePopu;i++){
        int val = directResultat(pop->solutions[i],instance);
        if(val > fbest){
            fbest = val;
            indiceSolutionBest = i;
        }
    }

    memcpy(solutionBest,pop->solutions[indiceSolutionBest],instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    int nbIte = 0;
    while(nbIte < nbIteMax){
        Population *enfant = malloc(sizeof(Population));
        initPopulation(enfant,taillePopu,DIRECT);

        for(int i=0;i<taillePopu/2;i++){
            int parentsSelect[4];
            int parents[2];

            //On séléctionne 4 parents aléatoires
            int *permutation = malloc(pop->taillePopu*sizeof(int));
            int * intermediaire = (int*)malloc( (pop->taillePopu) * sizeof(int));
            for(int i=0; i < pop->taillePopu; i++){
                intermediaire[i] = i+1;
            }

            for(int i=0; i < pop->taillePopu; i++){
                permutation[i] = intermediaire[rand() % (pop->taillePopu - (i))];
                retraitElemTab(&intermediaire,pop->taillePopu-(i),permutation[i]);
            }
            free(intermediaire);

            for(int j=0; j<4; j++){
                parentsSelect[j] = permutation[j];
                //printf("%d ",directResultat(pop->solutions[parentsSelect[j]-1],instance));
            }

            free(permutation);

            //On sélectionne les 2 meilleurs parents
            //printf("- MEILLEURS : ");
            int valeursmax[2];
            int resultat;
            parents[0] = parentsSelect[0]-1;
            parents[1] = parentsSelect[1]-1;
            valeursmax[0] = 0;
            valeursmax[1] = 0;
            for(int j=0; j<4;j++){
                resultat = directResultat(pop->solutions[parentsSelect[j]-1],instance);
                if(resultat > valeursmax[0]){
                    parents[0] = parentsSelect[j]-1;
                    valeursmax[0] = resultat;
                }
            }
            for(int j=0; j<4;j++){
                resultat = directResultat(pop->solutions[parentsSelect[j]-1],instance);
                if((resultat > valeursmax[1]) && (resultat < valeursmax[0])){
                    parents[1] = parentsSelect[j]-1;
                    valeursmax[1] = resultat;
                }
            }
            //printf("%d %d\n",directResultat(pop->solutions[parents[0]],instance),directResultat(pop->solutions[parents[1]],instance));
            //printf("%d %d\n",valeursmax[0],valeursmax[1]);

            //On créée des enfants
            int *enfant1 = malloc(instance->objetNb*sizeof(int));
            int *enfant2 = malloc(instance->objetNb*sizeof(int));
            procreerDirect(pop->solutions[parents[0]],pop->solutions[parents[1]],enfant1,enfant2,instance);

            //On ajoute les solution dans la pop enfant
            enfant->solutions[i*2] = enfant1;
            enfant->solutions[i*2+1] = enfant2;
            /*int valEnfant1,valEnfant2;
            valEnfant1 = directResultat(enfant1,instance);
            valEnfant2 = directResultat(enfant2,instance);
            printf("-----------\n");
            printf("val enfant 1 %d, val enfant 2 %d\n",valEnfant1,valEnfant2);*/
            //affSoluce(pop->solutions[parents[0]],instance->objetNb);
            //affSoluce(pop->solutions[parents[1]],instance->objetNb);
            //affSoluce(enfant1,instance->objetNb);
            //printf("point crois %d, deux copie %d, total %d\n\n",pointCroisement,instance->objetNb-pointCroisement,instance->objetNb-pointCroisement+pointCroisement);

            //printf("PARENT 1 : %d, PARENT 2 : %d\n",parents[0],parents[1]);
        }

        for(int i=0;i<taillePopu;i++){
            int resultat = directResultat(enfant->solutions[i],instance);
            if(resultat > fbest){
                fbest = resultat;
                memcpy(solutionBest,enfant->solutions[i],instance->objetNb*sizeof(int));
            }
            int tirageAleatoireMutation = rand() % 100 + 1; //On tire un nombre entre 1 et 100
            if(tirageAleatoireMutation < pMut){ //si le nombre tiré est inférieur à la proba de mutation, on mute l'enfant
                mutationDirect(enfant->solutions[i],instance);
                //printf("mutationnnnnnnnnn\n");
                if(resultat > fbest){
                    fbest = resultat;
                    memcpy(solutionBest,enfant->solutions[i],instance->objetNb*sizeof(int));
                }
            }
        }
        renouvellerDirect(pop,enfant,instance);
        detruirePopulation(enfant);

        nbIte++;
    }

    memcpy(tab,solutionBest,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    detruirePopulation(pop);
    free(solutionBest);
}

void procreerDirect(int *parent1, int *parent2, int *enfant1, int *enfant2, Instance *instance){
    int pointCroisement = rand() % instance->objetNb;
    memcpy(enfant1,parent1,pointCroisement*sizeof(int));
    memcpy(enfant1+pointCroisement,parent2+pointCroisement,(instance->objetNb-pointCroisement)*sizeof(int));
    memcpy(enfant2,parent2,pointCroisement*sizeof(int));
    memcpy(enfant2+pointCroisement,parent1+pointCroisement,(instance->objetNb-pointCroisement)*sizeof(int));

    //On teste si les solutions sont vérifiables, si ce n'est pas le cas on remet des 0 aléatoirement dans la solution
    while(directFaisable(enfant1,instance) == 0){
        enfant1[rand() % instance->objetNb] = 0;
    }
    while(directFaisable(enfant2,instance) == 0){
        enfant2[rand() % instance->objetNb] = 0;
    }
}

void mutationDirect(int *membre, Instance *instance){
    //On mute l'enfant
    int randNb;
    do{
        randNb = rand() % instance->objetNb;
    }while(membre[randNb] == 0);

    //On corrige la mutation si elle n'est pas faisable
    while(directFaisable(membre,instance) == 0){
        membre[rand() % instance->objetNb] = 0;
    }
}

void renouvellerDirect(Population *aEvoluer, Population *nouvelle, Instance *instance){
    int *zeros = malloc(instance->objetNb*sizeof(int));
    memset(zeros,0,instance->objetNb*sizeof(int));

    /*printf("ANCIEN \n");
    for(int i=0;i<aEvoluer->taillePopu;i++){
        printf("%d\n",directResultat(aEvoluer->solutions[i],instance));
    }*/
    /*printf("PROPOSITIONS \n");
    for(int i=0;i<aEvoluer->taillePopu;i++){
        printf("%d\n",directResultat(nouvelle->solutions[i],instance));
    }*/

    for(int i=0;i<aEvoluer->taillePopu;i++){
        int jmax=-1;
        for(int j=0;j<nouvelle->taillePopu;j++){
            if(directResultat(nouvelle->solutions[j],instance) >= directResultat(aEvoluer->solutions[i],instance)){
                jmax=j;
                memcpy(aEvoluer->solutions[i],nouvelle->solutions[j],instance->objetNb*sizeof(int));
            }
        }
        if(jmax>=0){
            //printf("jmax : %d",jmax);
            memcpy(nouvelle->solutions[jmax],zeros,instance->objetNb*sizeof(int));
        }
    }

    /*printf("NOUVEAU \n");
    for(int i=0;i<aEvoluer->taillePopu;i++){
        printf("%d\n",directResultat(aEvoluer->solutions[i],instance));
    }
    printf("--------------\n");*/
}

/*
|||||||||||||||||||||||||||||||||||||||||||||||

               PARTIE INDIRECTE

|||||||||||||||||||||||||||||||||||||||||||||||
*/

/** Metaheuristique génétique indirect
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param taillePopu la taille de la population à utiliser
 * @param pMut la probabilité de mutation d'un enfant
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaGenetiqueIndirecte(int* tab, Instance *instance, int nbIteMax, int taillePopu, int pMut){
    Population *pop = malloc(sizeof(Population));
    creerPopulation(pop,taillePopu,INDIRECT,instance);
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solution = calloc(instance->objetNb,sizeof(int)); //En codage direct
    int fbest = 0;
    int indiceSolutionBest  = 0;
    for(int i=0;i<pop->taillePopu;i++){
        decode(pop->solutions[i],solution,instance);
        int val = directResultat(solution,instance);
        if(val > fbest){
            fbest = val;
            indiceSolutionBest = i;
        }
    }

    memcpy(solutionBest,pop->solutions[indiceSolutionBest],instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest
    //affSoluce(solutionBest,100);

    int nbIte = 0;
    while(nbIte < nbIteMax){
        Population *enfant = malloc(sizeof(Population));
        initPopulation(enfant,taillePopu,DIRECT);

        for(int i=0;i<taillePopu/2;i++){
            int parentsSelect[4];
            int parents[2];

            //On séléctionne 4 parents aléatoires
            int *permutation = malloc(pop->taillePopu*sizeof(int));
            int * intermediaire = (int*)malloc( (pop->taillePopu) * sizeof(int));
            for(int i=0; i < pop->taillePopu; i++){
                intermediaire[i] = i+1;
            }

            for(int i=0; i < pop->taillePopu; i++){
                permutation[i] = intermediaire[rand() % (pop->taillePopu - (i))];
                retraitElemTab(&intermediaire,pop->taillePopu-(i),permutation[i]);
            }
            free(intermediaire);

            for(int j=0; j<4; j++){
                parentsSelect[j] = permutation[j];
                //printf("%d ",directResultat(pop->solutions[parentsSelect[j]-1],instance));
            }

            free(permutation);

            //On sélectionne les 2 meilleurs parents
            //printf("- MEILLEURS : ");
            int valeursmax[2];
            int resultat;
            parents[0] = parentsSelect[0]-1;
            parents[1] = parentsSelect[1]-1;
            valeursmax[0] = 0;
            valeursmax[1] = 0;
            for(int j=0; j<4;j++){
                decode(pop->solutions[parentsSelect[j]-1],solution,instance);
                resultat = directResultat(solution,instance);
                if(resultat > valeursmax[0]){
                    parents[0] = parentsSelect[j]-1;
                    valeursmax[0] = resultat;
                }
            }
            for(int j=0; j<4;j++){
                decode(pop->solutions[parentsSelect[j]-1],solution,instance);
                resultat = directResultat(solution,instance);
                if((resultat > valeursmax[1]) && (resultat < valeursmax[0])){
                    parents[1] = parentsSelect[j]-1;
                    valeursmax[1] = resultat;
                }
            }
            //printf("%d %d\n",directResultat(pop->solutions[parents[0]],instance),directResultat(pop->solutions[parents[1]],instance));
            //printf("%d %d\n",valeursmax[0],valeursmax[1]);

            //On créée des enfants
            int *enfant1 = malloc(instance->objetNb*sizeof(int));
            int *enfant2 = malloc(instance->objetNb*sizeof(int));
            procreerIndirect(pop->solutions[parents[0]],pop->solutions[parents[1]],enfant1,enfant2,instance);

            //On ajoute les solution dans la pop enfant
            enfant->solutions[i*2] = enfant1;
            enfant->solutions[i*2+1] = enfant2;
            /*int valEnfant1,valEnfant2;
            valEnfant1 = directResultat(enfant1,instance);
            valEnfant2 = directResultat(enfant2,instance);
            printf("-----------\n");
            printf("val enfant 1 %d, val enfant 2 %d\n",valEnfant1,valEnfant2);*/
            //affSoluce(pop->solutions[parents[0]],instance->objetNb);
            //affSoluce(pop->solutions[parents[1]],instance->objetNb);
            //affSoluce(enfant1,instance->objetNb);
            //printf("point crois %d, deux copie %d, total %d\n\n",pointCroisement,instance->objetNb-pointCroisement,instance->objetNb-pointCroisement+pointCroisement);

            //printf("PARENT 1 : %d, PARENT 2 : %d\n",parents[0],parents[1]);
        }

        for(int i=0;i<taillePopu;i++){
            int resultat = directResultat(enfant->solutions[i],instance);
            if(resultat > fbest){
                fbest = resultat;
                memcpy(solutionBest,enfant->solutions[i],instance->objetNb*sizeof(int));
            }
            int tirageAleatoireMutation = rand() % 100 + 1; //On tire un nombre entre 1 et 100
            if(tirageAleatoireMutation < pMut){ //si le nombre tiré est inférieur à la proba de mutation, on mute l'enfant
                mutationDirect(enfant->solutions[i],instance);
                //printf("mutationnnnnnnnnn\n");
                if(resultat > fbest){
                    fbest = resultat;
                    memcpy(solutionBest,enfant->solutions[i],instance->objetNb*sizeof(int));
                }
            }
        }
        renouvellerDirect(pop,enfant,instance);
        detruirePopulation(enfant);

        nbIte++;
    }

    memcpy(tab,solutionBest,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    detruirePopulation(pop);
    free(solutionBest);
}

/** Algo PMX**/
void procreerIndirect(int *parent1, int *parent2, int *enfant1, int *enfant2, Instance *instance){
    int pointCroisement1 = rand() % instance->objetNb;
    int pointCroisement2;
    do{
        pointCroisement2 = rand() % instance->objetNb;
    }
    while(pointCroisement1 == pointCroisement2);

    //On s'assure que le point de croisement 2 est toujours le deuxième point de coupure (donc > au pt 1)
    if(pointCroisement1 > pointCroisement2){
        int tmp = pointCroisement1;
        pointCroisement1 = pointCroisement2;
        pointCroisement2 = tmp;
    }

    memset(enfant1,0,100*sizeof(int));
    memcpy(enfant1+pointCroisement1,parent2+pointCroisement1,(pointCroisement2-pointCroisement1)*sizeof(int));
    memcpy(enfant2+pointCroisement1,parent1+pointCroisement1,(pointCroisement2-pointCroisement1)*sizeof(int));

    printf("pt1 %d, pt2 %d\n",pointCroisement1,pointCroisement2);
    affSoluce(enfant1,100);

    /*memcpy(enfant1+pointCroisement,parent2+pointCroisement,(instance->objetNb-pointCroisement)*sizeof(int));
    memcpy(enfant2,parent2,pointCroisement*sizeof(int));
    memcpy(enfant2+pointCroisement,parent1+pointCroisement,(instance->objetNb-pointCroisement)*sizeof(int));*/
}
