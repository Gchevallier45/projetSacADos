#include "genetique.h"

// --------------------------------------------------------------------------------------
// Ce fichier contient toutes les fonctions en relation avec la métaheuristique génétique
// --------------------------------------------------------------------------------------

/** Initialise une population vide de type direct ou indirect
 * @param population un pointeur de type Population, non initialisé
 * @param taillePopulation la taille de la population
 * @param typeSolutions type direct ou indirect
 */
void initPopulation(Population *population, int taillePopulation, int typeSolutions){
    population->taillePopu = taillePopulation;
    population->type = typeSolutions;
    population->solutions = (int**)malloc(taillePopulation*sizeof(int*));
}

/** Initialise et génère une population de type direct ou indirect
 * @param population un pointeur de type Population, non initialisé
 * @param taillePopulation la taille de la population
 * @param typeSolutions type direct ou indirect
 * @param instance l'instance à utiliser pour générer la population
 */
void creerPopulation(Population *population, int taillePopulation, int typeSolutions, Instance *instance){
    population->taillePopu = taillePopulation;
    population->type = typeSolutions;
    population->solutions = (int**)malloc(taillePopulation*sizeof(int*));
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
            randPick(solution, instance);
            population->solutions[i] = solution;
        }
    }
}

/** Détruit une population
 * @param population la population à détruire
 */
void detruirePopulation(Population *population){
    for(int i=0;i<population->taillePopu;i++){
        free(population->solutions[i]);
    }
    free(population->solutions);
    free(population);
}


/**
|||||||||||||||||||||||||||||||||||||||||||||||

               PARTIE DIRECTE

|||||||||||||||||||||||||||||||||||||||||||||||
**/


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
            }

            free(permutation);

            //On sélectionne les 2 meilleurs parents
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

            //On créée des enfants
            int *enfant1 = malloc(instance->objetNb*sizeof(int));
            int *enfant2 = malloc(instance->objetNb*sizeof(int));
            procreerDirect(pop->solutions[parents[0]],pop->solutions[parents[1]],enfant1,enfant2,instance);

            //On ajoute les solution dans la pop enfant
            enfant->solutions[i*2] = enfant1;
            enfant->solutions[i*2+1] = enfant2;
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

/** Génère deux enfants au format direct à partir de deux parents donnés
 * @param parent1, parent2 les parents à utiliser
 * @param enfant1, enfant2 pointeurs dans lesquels seront stockés les 2 enfants
 * @param instance l'instance associée aux deux parents
 * Préconditions : parent1, parent2, enfant1 et enfant2 correctement initialisés
 */
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

/** Mute un membre de la population au format direct
 * @param membre le membre à muter
 * @param instance l'instance associée au membre
 * Préconditions : membre correctement initialisé
 */
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

/** Renouvelle une population à partir d'une nouvelle population de façon à ne garder que les meilleurs membres des 2 populations
 * @param aEvoluer la population à renouveller
 * @param nouvelle la population à utiliser pour le renouvellement
 * @param instance l'instance associée aux populations
 * Préconditions : populations initialisées et non vides
 */
void renouvellerDirect(Population *aEvoluer, Population *nouvelle, Instance *instance){
    int *zeros = malloc(instance->objetNb*sizeof(int));
    memset(zeros,0,instance->objetNb*sizeof(int));

    for(int i=0;i<aEvoluer->taillePopu;i++){
        int jmax=-1;
        for(int j=0;j<nouvelle->taillePopu;j++){
            if(directResultat(nouvelle->solutions[j],instance) >= directResultat(aEvoluer->solutions[i],instance)){
                jmax=j;
                memcpy(aEvoluer->solutions[i],nouvelle->solutions[j],instance->objetNb*sizeof(int));
            }
        }
        if(jmax>=0){
            memcpy(nouvelle->solutions[jmax],zeros,instance->objetNb*sizeof(int));
        }
    }
}


/**
|||||||||||||||||||||||||||||||||||||||||||||||

               PARTIE INDIRECTE

|||||||||||||||||||||||||||||||||||||||||||||||
**/


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
        memset(solution,0,instance->objetNb*sizeof(int));
        decode(pop->solutions[i],solution,instance);
        int val = directResultat(solution,instance);
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
            }

            free(permutation);

            //On sélectionne les 2 meilleurs parents
            int valeursmax[2];
            int resultat;
            parents[0] = parentsSelect[0]-1;
            parents[1] = parentsSelect[1]-1;
            valeursmax[0] = 0;
            valeursmax[1] = 0;
            for(int j=0; j<4;j++){
                memset(solution,0,instance->objetNb*sizeof(int));
                decode(pop->solutions[parentsSelect[j]-1],solution,instance);
                resultat = directResultat(solution,instance);
                if(resultat > valeursmax[0]){
                    parents[0] = parentsSelect[j]-1;
                    valeursmax[0] = resultat;
                }
            }
            for(int j=0; j<4;j++){
                memset(solution,0,instance->objetNb*sizeof(int));
                decode(pop->solutions[parentsSelect[j]-1],solution,instance);
                resultat = directResultat(solution,instance);
                if((resultat > valeursmax[1]) && (resultat < valeursmax[0])){
                    parents[1] = parentsSelect[j]-1;
                    valeursmax[1] = resultat;
                }
            }

            //On créée des enfants
            int *enfant1 = malloc(instance->objetNb*sizeof(int));
            int *enfant2 = malloc(instance->objetNb*sizeof(int));
            procreerIndirect(pop->solutions[parents[0]],pop->solutions[parents[1]],enfant1,enfant2,instance);

            //On ajoute les solution dans la pop enfant
            enfant->solutions[i*2] = enfant1;
            enfant->solutions[i*2+1] = enfant2;
        }

        for(int i=0;i<taillePopu;i++){
            memset(solution,0,instance->objetNb*sizeof(int));
            decode(enfant->solutions[i],solution,instance);
            int resultat = directResultat(solution,instance);
            if(resultat > fbest){
                fbest = resultat;
                memcpy(solutionBest,enfant->solutions[i],instance->objetNb*sizeof(int));
            }
            int tirageAleatoireMutation = rand() % 100 + 1; //On tire un nombre entre 1 et 100
            if(tirageAleatoireMutation < pMut){ //si le nombre tiré est inférieur à la proba de mutation, on mute l'enfant
                mutationIndirect(enfant->solutions[i],instance);
                if(resultat > fbest){
                    fbest = resultat;
                    memcpy(solutionBest,enfant->solutions[i],instance->objetNb*sizeof(int));
                }
            }
        }
        renouvellerIndirect(pop,enfant,instance);
        detruirePopulation(enfant);

        nbIte++;
    }

    //Copie de la solution dans le tableau de destination
    memset(solution,0,instance->objetNb*sizeof(int));
    decode(solutionBest,solution,instance);
    memcpy(tab,solution,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest

    detruirePopulation(pop);
    free(solutionBest);
    free(solution);
}

/** Génère deux enfants au format indirect à partir de deux parents donnés
 * @param parent1, parent2 les parents à utiliser
 * @param enfant1, enfant2 pointeurs dans lesquels seront stockés les 2 enfants
 * @param instance l'instance associée aux deux parents
 * Préconditions : parent1, parent2, enfant1 et enfant2 correctement initialisés
 */
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

    memset(enfant1,0,instance->objetNb*sizeof(int));
    memset(enfant2,0,instance->objetNb*sizeof(int));
    memcpy(enfant1+pointCroisement1,parent1+pointCroisement1,(pointCroisement2-pointCroisement1+1)*sizeof(int));
    memcpy(enfant2+pointCroisement1,parent2+pointCroisement1,(pointCroisement2-pointCroisement1+1)*sizeof(int));

    PMX(parent1,parent2,enfant1,pointCroisement1,pointCroisement2,instance);
    PMX(parent2,parent1,enfant2,pointCroisement1,pointCroisement2,instance);

}

/** Algorithme PMX pour créer un enfant en solution indirecte à partir de 2 parents
 * @param parent1, parent2 les parents à utiliser
 * @param enfant pointeur sur la solution enfant
 * @param pointCroisement1, pointCroisement2 les points de croisements à utiliser
 * @param instance l'instance associée aux deux parents
 * Préconditions : parent1, parent2, enfant1 et enfant2 correctement initialisés
**/
void PMX(int *parent1, int *parent2, int *enfant, int pointCroisement1, int pointCroisement2, Instance *instance){

    /* On regarde d'abord si les éléments de parent1 et parent2 sont identiques entre les points de croisement
       Si c'est le cas, on a pas besoin d'exécuter toutes les étapes de l'algo PMX, la permutation peut être faite directement
    */
    if(memcmp(enfant+pointCroisement1,parent2+pointCroisement1,(pointCroisement2-pointCroisement1+1)*sizeof(int)) != 0){
        //On cherche les valeurs qui différent dans parent1 et parent2 entre les deux points de croisement
        int *diffValeurs, nbValeurs=0;
        diffValeurs = malloc(0);
        for(int i=pointCroisement1;i<pointCroisement2+1;i++){
            int trouve=0;
            for(int j=pointCroisement1;j<pointCroisement2+1;j++){
                if(parent2[i]==parent1[j]){
                    trouve=1;
                    break;
                }
            }

            if(trouve == 0){
                nbValeurs++;
                diffValeurs = realloc(diffValeurs,nbValeurs*sizeof(int));
                diffValeurs[nbValeurs-1]=parent2[i];
            }
        }

        //Pour chaque valeur qui diffère on calcule l'endroit où la placer pour ne pas avoir d'objets en double dans la solution enfant
        for(int i=0;i<nbValeurs;i++){
            int indiceValeur=0, objetAChercher = diffValeurs[i];
            do{
                for(int j=0;j<instance->objetNb;j++){
                    if(objetAChercher == parent2[j]){
                        indiceValeur = j;
                        objetAChercher = parent1[j];
                        break;
                    }
                }
            }
            while(indiceValeur>=pointCroisement1 && indiceValeur<=pointCroisement2);
            enfant[indiceValeur] = diffValeurs[i];
        }

        free(diffValeurs);
    }

    //On construit le reste de la solution en copiant les objets de la solution parent2 dans la solution enfant
    for(int i=0;i<instance->objetNb;i++){
        if(enfant[i] == 0){
            enfant[i] = parent2[i];
        }
    }


}

/** Mute un membre de la population au format indirect
 * @param membre le membre à muter
 * @param instance l'instance associée au membre
 * Préconditions : membre correctement initialisé
 */
void mutationIndirect(int *membre, Instance *instance){
    //On tire au hasard deux indices du tableau à échanger
    int indice1 = rand() % instance->objetNb;
    int indice2;
    do{
        indice2 = rand() % instance->objetNb;
    }
    while(indice1 == indice2);

    //On échange les deux objets
    int tmp;
    tmp = membre[indice1];
    membre[indice1] = membre[indice2];
    membre[indice2] = tmp;
}

/** Renouvelle une population à partir d'une nouvelle population de façon à ne garder que les meilleurs membres des 2 populations
 * @param aEvoluer la population à renouveller
 * @param nouvelle la population à utiliser pour le renouvellement
 * @param instance l'instance associée aux populations
 * Préconditions : populations initialisées et non vides
 */
void renouvellerIndirect(Population *aEvoluer, Population *nouvelle, Instance *instance){
    int *zeros = malloc(instance->objetNb*sizeof(int));
    memset(zeros,0,instance->objetNb*sizeof(int));

    int *aEvoluerDirect = calloc(instance->objetNb,sizeof(int));
    int *nouvelleDirect = calloc(instance->objetNb,sizeof(int));

    for(int i=0;i<aEvoluer->taillePopu;i++){
        int jmax=-1;
        for(int j=0;j<nouvelle->taillePopu;j++){
            memset(aEvoluerDirect,0,instance->objetNb*sizeof(int));
            memset(nouvelleDirect,0,instance->objetNb*sizeof(int));
            decode(aEvoluer->solutions[i],aEvoluerDirect,instance);
            decode(nouvelle->solutions[j],nouvelleDirect,instance);
            if(directResultat(nouvelleDirect,instance) >= directResultat(aEvoluerDirect,instance)){
                jmax=j;
                memcpy(aEvoluer->solutions[i],nouvelle->solutions[j],instance->objetNb*sizeof(int));
            }
        }
        if(jmax>=0){
            memcpy(nouvelle->solutions[jmax],zeros,instance->objetNb*sizeof(int));
        }
    }

    free(aEvoluerDirect);
    free(nouvelleDirect);
    free(zeros);
}
