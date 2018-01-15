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

/** Metaheuristique locale directe
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaLocalDirecte(int* tab, Instance *instance){
    int *solutionCourante = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int *solutionVoisine = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int *solutionBestVoisine = malloc(instance->objetNb*sizeof(int)); //En codage direct

    Direct(solutionCourante, instance,3); //On génère la solution de départ avec l'algo d'ordonnancement le + performant
    memcpy(solutionBest,solutionCourante,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest
    memcpy(solutionBestVoisine,solutionCourante,instance->objetNb*sizeof(int));

    //Calcul de fbest
    int fbest = directResultat(solutionCourante,instance);
    int continuer = 1;
    int fcourant = fbest;
    int fprec = fcourant;

    while(continuer == 1){
        memcpy(solutionVoisine,solutionCourante,instance->objetNb*sizeof(int));
        int fbestvoisin = 0;
        for(int i=0;i<instance->objetNb;i++){ //Première boucle for qui permet de changer les 0 en 1
            if(solutionVoisine[i]==0){
                //On met l'objet i dans le sac
                solutionVoisine[i] = 1;

                //Evaluation de la solution voisine
                int resultat=directResultat(solutionVoisine,instance);
                if(resultat > fbestvoisin && directFaisable(solutionVoisine,instance) == 1){
                    memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                    fbestvoisin = resultat;
                }

                //On le retire du sac pour passer à une autre solution
                solutionVoisine[i] = 0;
            }
        }

        for(int i=0;i<instance->objetNb;i++){ //Deuxième boucle for qui permet de permuter des éléments
            if(solutionVoisine[i] == 1){
                for(int j=0;j<instance->objetNb;j++){
                    if(solutionVoisine[j] == 0){
                        //Permutation des éléments
                        solutionVoisine[i] = 0;
                        solutionVoisine[j] = 1;

                        //Evaluation de la solution voisine
                        int resultat=directResultat(solutionVoisine,instance);
                        if(resultat > fbestvoisin && directFaisable(solutionVoisine,instance) == 1){
                            memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                            fbestvoisin = resultat;
                        }

                        //Permutation des éléments
                        solutionVoisine[i] = 1;
                        solutionVoisine[j] = 0;

                    }
                }
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
    memcpy(tab,solutionBest,instance->objetNb*sizeof(int));

    free(solutionCourante);
    free(solutionBest);
    free(solutionVoisine);
    free(solutionBestVoisine);
}

/** Metaheuristique tabou indirecte
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param TabouSize le nombre de solutions taboues
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */

void metaTabouIndirecte(int* tab, Instance *instance, int nbIteMax, int tabouSize, int aspi){
    int *solutionCourante = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solutionVoisine = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solutionBestVoisine = malloc(instance->objetNb*sizeof(int)); //En codage indirect
    int *solution = calloc(instance->objetNb,sizeof(int)); //En codage direct

    int tabou[tabouSize][2];
    for(int i = 0; i<tabouSize;i++)
        memset(tabou[i],0,2);

    decRatioValPoidsPick(solutionCourante, instance); //On génère la solution de départ avec l'algo d'ordonnancement le + performant
    memcpy(solutionBest,solutionCourante,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest
    memcpy(solutionBestVoisine,solutionCourante,instance->objetNb*sizeof(int));

    //Calcul de fbest
    decode(solutionCourante,instance->objetNb,solution,instance);
    int fbest = directResultat(solution,instance);
    int continuer = 1;
    int fcourant = fbest;
    int fprec = fcourant;

    int k = 0;
    int p;
    int flag;

    while(continuer == 1){
        memcpy(solutionVoisine,solutionCourante,instance->objetNb*sizeof(int));
        int fbestvoisin = 0;
        for(int i=0;i<instance->objetNb/2;i++){
            for(int j=i+1;j<instance->objetNb;j++){ //j=i+1 car les permutations de 0 à i+1 ont déjà été effectuées dans les itérations d'avant
                //Permutation des éléments
                flag = 0;
                for(p = 0; p < tabouSize; p++){
                    if((solutionVoisine[i] == tabou[p][0] && solutionVoisine[j] == tabou[p][1]) || (solutionVoisine[i] == tabou[p][1] && solutionVoisine[j] == tabou[p][0]))
                        flag = 1;
                }
                if( (flag == 1 && aspi == 1) || flag == 0){

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
        }
        //comparaison de la solutioncourante avec bestsolutionvoisine et regarde l'élément qui a changé
        for(int i = 0; i<instance->objetNb; i++){
            if(solutionCourante[i] != solutionBestVoisine[i]){
                tabou[k][0] = solutionCourante[i];
                tabou[k][1] = solutionBestVoisine[i];
                k++;
            }
        }
        if (k == tabouSize) //si la liste de tabou est remplie on recommence à le remplir du début
            k = 0;

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

/** Metaheuristique tabou directe
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaTabouDirecte(int* tab, Instance *instance, int nbIteMax, int aspi, int tailleListe){
    int *solutionCourante = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int *solutionBest = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int *solutionVoisine = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int *solutionBestVoisine = malloc(instance->objetNb*sizeof(int)); //En codage direct
    int nbMouvements = 0;
    int **listeMouvements = malloc(nbMouvements*sizeof(int*));

    Direct(solutionCourante, instance,3); //On génère la solution de départ avec l'algo d'ordonnancement le + performant
    memcpy(solutionBest,solutionCourante,instance->objetNb*sizeof(int)); //Copie de solutionCourante dans solutionBest
    memcpy(solutionBestVoisine,solutionCourante,instance->objetNb*sizeof(int));

    //Calcul de fbest
    int fbest = directResultat(solutionCourante,instance);
    int nbIte = 0;
    int fcourant = fbest;

    int mouvementUtil[2];
    while(nbIte < nbIteMax){
        mouvementUtil[0] = -1;
        mouvementUtil[1] = -1;
        memcpy(solutionVoisine,solutionCourante,instance->objetNb*sizeof(int));
        int fbestvoisin = 0;
        for(int i=0;i<instance->objetNb;i++){ //Première boucle for qui permet de changer les 0 en 1
            if(solutionVoisine[i]==0){
                int estTabou = 0;
                for(int itabou = 0;itabou<nbMouvements;itabou++){
                    if(listeMouvements[itabou][0] == i && listeMouvements[itabou][1] == i){
                        estTabou = 1;
                        break;
                    }
                }

                if(estTabou == 0 || aspi == 1){
                    //On met l'objet i dans le sac
                    solutionVoisine[i] = 1;

                    //Evaluation de la solution voisine
                    int resultat=directResultat(solutionVoisine,instance);

                    if(estTabou == 0){
                        if(resultat > fbestvoisin && directFaisable(solutionVoisine,instance) == 1){
                            memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                            fbestvoisin = resultat;
                            mouvementUtil[0] = i;
                            mouvementUtil[1] = i;
                        }
                    }
                    else{
                        if(resultat > fbest && directFaisable(solutionVoisine,instance) == 1){
                            memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                            fbestvoisin = resultat;
                            mouvementUtil[0] = i;
                            mouvementUtil[1] = i;
                        }
                    }

                    //On le retire du sac pour passer à une autre solution
                    solutionVoisine[i] = 0;
                }
            }
        }

        for(int i=0;i<instance->objetNb;i++){ //Deuxième boucle for qui permet de permuter des éléments
            if(solutionVoisine[i] == 1){
                for(int j=0;j<instance->objetNb;j++){
                    if(solutionVoisine[j] == 0){
                        int estTabou = 0;
                        for(int itabou = 0;itabou<nbMouvements;itabou++){
                            if((listeMouvements[itabou][0] == i || listeMouvements[itabou][0] == j) && (listeMouvements[itabou][1] == i || listeMouvements[itabou][1] == j)){
                                estTabou = 1;
                                break;
                            }
                        }

                        if(estTabou == 0 || aspi == 1){
                            //Permutation des éléments
                            solutionVoisine[i] = 0;
                            solutionVoisine[j] = 1;

                            //Evaluation de la solution voisine
                            int resultat=directResultat(solutionVoisine,instance);

                            if(estTabou == 0){
                                if(resultat > fbestvoisin && directFaisable(solutionVoisine,instance) == 1){
                                    memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                                    fbestvoisin = resultat;
                                    mouvementUtil[0] = i;
                                    mouvementUtil[1] = j;
                                }
                            }
                            else{
                                if(resultat > fbest && directFaisable(solutionVoisine,instance) == 1){
                                    memcpy(solutionBestVoisine,solutionVoisine,instance->objetNb*sizeof(int));
                                    fbestvoisin = resultat;
                                    mouvementUtil[0] = i;
                                    mouvementUtil[1] = j;
                                }
                            }

                            //Permutation des éléments
                            solutionVoisine[i] = 1;
                            solutionVoisine[j] = 0;
                        }

                    }
                }
            }
        }

        fcourant = fbestvoisin;
        memcpy(solutionCourante,solutionBestVoisine,instance->objetNb*sizeof(int));

        /*printf("-----\n");
        for (int i=0; i<nbMouvements;i++)
            affSoluce(listeMouvements[i],2);
        printf("\n");*/

        int estTabou = 0;
        for(int itabou = 0;itabou<nbMouvements;itabou++){
            if((listeMouvements[itabou][0] == mouvementUtil[0] || listeMouvements[itabou][0] == mouvementUtil[1]) && (listeMouvements[itabou][1] == mouvementUtil[0] || listeMouvements[itabou][1] == mouvementUtil[1])){
                estTabou = 1;
                break;
            }
        }

        if(nbMouvements < tailleListe){ //On teste si le nombre de mouvements est inférieur ou égal à la taille max de la liste
            if(estTabou == 0)
                nbMouvements++;
            listeMouvements = realloc(listeMouvements,nbMouvements*sizeof(int*));
            listeMouvements[nbMouvements-1] = malloc(2*sizeof(int));
            listeMouvements[nbMouvements-1][0]=mouvementUtil[0];
            listeMouvements[nbMouvements-1][1]=mouvementUtil[1];
        }
        else{ //Sinon on décale de tableau pour stocker la dernière permutation
            listeMouvements[nbIte%nbMouvements][0]=mouvementUtil[0];
            listeMouvements[nbIte%nbMouvements][1]=mouvementUtil[1];
        }

        /*printf("%d\n",nbMouvements);
        printf("%d %d\n",mouvementUtil[0],mouvementUtil[1]);
        printf("est tabou ? %d\n",estTabou);
        affSoluce(solutionCourante,instance->objetNb);
        printf("%d\n",directResultat(solutionCourante,instance));
        for (int i=0; i<nbMouvements;i++)
            affSoluce(listeMouvements[i],2);
        printf("-----\n");*/

        if(fcourant>fbest){
            fbest=fcourant;
            memcpy(solutionBest,solutionCourante,instance->objetNb*sizeof(int));
            nbIte=0;
        }

        nbIte++;
    }

    //Copie de la solution dans le tableau de destination
    memcpy(tab,solutionBest,instance->objetNb*sizeof(int));

    free(solutionCourante);
    free(solutionBest);
    free(solutionVoisine);
    free(solutionBestVoisine);
    free(listeMouvements);
}
