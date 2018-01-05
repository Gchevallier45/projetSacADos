#include "heuristique.h"

/** Supprime un élément d'un tableau
 * @param tabElem l'adresse d'un tableau de int contenant les objets du sac
 * @param tabTaille la taille du tableau tabElem
 * @param elem l'élément du tableau à supprimer (et non l'indice !)
 * Préconditions : tabElem non nul
 */
void retraitElemTab(int ** tabElem, int tabTaille, int elem){
    int indiceElem=0;
    /*while((*tabElem)[indiceElem]!=elem)
        indiceElem++;

    for(int i = indiceElem; i<tabTaille-1; i++){
        (*tabElem)[i] = (*tabElem)[i+1];
    }*/

    int *tmpElem = *tabElem;
    while(*tmpElem!=elem)
        tmpElem++;

    int i=tmpElem-*tabElem;
    for(i; i<tabTaille-1; i++){
        *tmpElem = *(tmpElem+1);
        tmpElem++;
    }

    *tabElem = realloc(*tabElem, sizeof(int)*(tabTaille-1));
}

/** Remplit un tableau avec une permutation d'objets aléatoire
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void randPick(int* tabAlea, Instance instance){
    int * intermediaire = (int*)malloc( (instance.objetNb) * sizeof(int));
    for(int i=0; i < instance.objetNb; i++){
        intermediaire[i] = i;
    }

    for(int i=0; i < instance.objetNb; i++){
        tabAlea[i] = intermediaire[rand() % (instance.objetNb - (i))];
        retraitElemTab(&intermediaire,instance.objetNb-(i),tabAlea[i]);
    }
    free(intermediaire);
}

/** Remplit un tableau avec une permutation d'objets de valeur décroissante
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decValPick(int* tabAlea, Instance instance){
    int * valeurs = (int*)malloc( (instance.objetNb) * sizeof(int));
    memcpy(valeurs, instance.Pj, instance.objetNb*sizeof(int));

    for(int i=0; i < instance.objetNb; i++){
        tabAlea[i] = i;
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = instance.objetNb;
    while(enOrdre == 0)
    {
        enOrdre = 1;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(valeurs[i] < valeurs[i+1])
            {
                int tmpVal = valeurs[i];
                valeurs[i] = valeurs[i+1];
                valeurs[i+1] = tmpVal;
                tmpVal = tabAlea[i];
                tabAlea[i] = tabAlea[i+1];
                tabAlea[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(valeurs);
}

/** Remplit un tableau avec une permutation d'objets avec un ratio valeur/sommedespoids décroissant
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decRatioValPoidsPick(int* tabAlea, Instance instance){
    double * ratios = (double*)malloc( (instance.objetNb) * sizeof(double));

    for(int i=0; i < instance.objetNb; i++){
        int sommePoids = 0;
        for(int j=0; j < instance.dimensionNb; j++){
            sommePoids += instance.Rij[j][i];
        }
        ratios[i] = instance.Pj[i]/(double)sommePoids;
    }

    for(int i=0; i < instance.objetNb; i++){
        tabAlea[i] = i;
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = instance.objetNb;
    while(enOrdre == 0)
    {
        enOrdre = 1;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(ratios[i] < ratios[i+1])
            {
                double tmpVal = ratios[i];
                ratios[i] = ratios[i+1];
                ratios[i+1] = tmpVal;
                tmpVal = tabAlea[i];
                tabAlea[i] = tabAlea[i+1];
                tabAlea[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(ratios);
}

/** Remplit un tableau avec une permutation d'objets avec un ratio valeur/sommedespoids sur la dimension critique décroissant
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decRatioValPoidsCritPick(int* tabAlea, int tailleTabAlea, Instance instance, int *etatDimensions){
    double * ratios = (double*)malloc( (tailleTabAlea) * sizeof(double));
    int dimensionCritique = 0;

    if(etatDimensions == NULL){
        int poidsMin = instance.Bi[0];
        for(int i=1; i < instance.dimensionNb; i++){
            if(instance.Bi[i] < poidsMin){
                poidsMin = instance.Bi[i];
                dimensionCritique = i;
            }
        }

        for(int i=0; i < tailleTabAlea; i++){
            tabAlea[i] = i;
        }
    }
    else{
        int poidsMin = etatDimensions[0];
        for(int i=1; i < instance.dimensionNb; i++){
            if(etatDimensions[i] < poidsMin){
                poidsMin = etatDimensions[i];
                dimensionCritique = i;
            }
        }
    }

    //printf(" dim crit :%d \n",dimensionCritique);

    for(int i=0; i < tailleTabAlea; i++){
        ratios[i] = instance.Pj[i]/(double)instance.Rij[dimensionCritique][i];
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = tailleTabAlea;
    while(enOrdre == 0)
    {
        enOrdre = 1;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(ratios[i] < ratios[i+1])
            {
                double tmpVal = ratios[i];
                ratios[i] = ratios[i+1];
                ratios[i+1] = tmpVal;
                tmpVal = tabAlea[i];
                tabAlea[i] = tabAlea[i+1];
                tabAlea[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(ratios);
}

/** Heuristique indirecte
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void Indirect(int* tabAlea, Instance instance, int typeOrdonnancement){

    int * solutionInd = (int*)malloc( (instance.objetNb) * sizeof(int));

    for(int i=0;i<instance.objetNb;i++)
        tabAlea[i] = 0;

    switch(typeOrdonnancement){
    case 1:
        randPick(solutionInd, instance);
        break;
    case 2:
        decValPick(solutionInd, instance);
        break;
    case 3:
        decRatioValPoidsPick(solutionInd, instance);
        break;
    case 4:
        decRatioValPoidsCritPick(solutionInd, instance.objetNb, instance, NULL);
        break;
    case 5:
        //Stratégie d'ordonnancement à développer
        break;
    }

    decode(solutionInd,instance.objetNb,tabAlea,instance);
    free(solutionInd);
}

/** Heuristique directe
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void Direct(int* tabAlea, Instance instance, int typeOrdonnancement){
    int * solutionInd = (int*)malloc( (instance.objetNb) * sizeof(int));
    int * solutionIndFirst = solutionInd;
    int *sommePoids = calloc(instance.dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension
    int *etatDimensions = calloc(instance.dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension

    for(int i=0;i<instance.objetNb;i++)
        tabAlea[i] = 0;

    switch(typeOrdonnancement){
    case 1:
        randPick(solutionInd, instance);
        break;
    case 2:
        decValPick(solutionInd, instance);
        break;
    case 3:
        decRatioValPoidsPick(solutionInd, instance);
        break;
    case 4:
        decRatioValPoidsCritPick(solutionInd, instance.objetNb, instance, NULL);
        break;
    case 5:
        //Stratégie d'ordonnancement à développer
        break;
    case 6: //Ratio valeur/poids mis à jour
        decRatioValPoidsCritPick(solutionInd, instance.objetNb, instance, NULL);
        for(int i=0;i<instance.dimensionNb;i++)
            etatDimensions[i] = instance.Bi[i];
        break;
    }

    for(int i=0;i<instance.objetNb;i++){
        int resultTest = 0;

        for(int j=0; j<instance.dimensionNb; j++){
            if(sommePoids[j]+instance.Rij[j][*solutionInd] < instance.Bi[j]){
                resultTest++;
            }
            else{
                break;
            }
        }

        if(resultTest == instance.dimensionNb){
            for(int j=0; j<instance.dimensionNb; j++){
                sommePoids[j]+=instance.Rij[j][*solutionInd];
            }
            tabAlea[*solutionInd] = 1;

            if(typeOrdonnancement == 6){
                for(int i=0;i<instance.dimensionNb;i++){
                    etatDimensions[i] -= instance.Rij[i][*solutionInd];
                    //printf("%d ",etatDimensions[i]);
                }
            }
        }

        solutionInd++; //Equivaut à supprimer le premier élément du tableau

        if(typeOrdonnancement == 6){
            decRatioValPoidsCritPick(solutionInd, instance.objetNb-i-1, instance, etatDimensions);
            /*for(int j=0; j < instance.objetNb-i-1; j++){
                printf(" %d|",solutionInd[j]);
            }
            printf("\n\n");*/
            //printf("après : %d \n",*solutionInd);
        }

    }
    free(sommePoids);
    free(solutionIndFirst);
    free(etatDimensions);
}
