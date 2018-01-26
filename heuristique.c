#include "heuristique.h"

/** Supprime un élément d'un tableau
 * @param tabElem l'adresse d'un tableau de int contenant les objets du sac
 * @param tabTaille la taille du tableau tabElem
 * @param elem l'élément du tableau à supprimer (et non l'indice !)
 * Préconditions : tabElem non nul
 */
void retraitElemTab(int ** tabElem, int tabTaille, int elem){
    int *tmpElem = *tabElem;
    while(*tmpElem!=elem)
        tmpElem++;

    int i=tmpElem-*tabElem;
    /*for(i; i<tabTaille-1; i++){
        *tmpElem = *(tmpElem+1);
        tmpElem++;
    }*/
    memcpy(tmpElem,tmpElem+1,(tabTaille-1-i)*sizeof(int));

    *tabElem = realloc(*tabElem, sizeof(int)*(tabTaille-1));
}

/** Remplit un tableau avec une permutation d'objets aléatoire
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void randPick(int* tab, Instance *instance){
    int * intermediaire = (int*)malloc( (instance->objetNb) * sizeof(int));
    for(int i=0; i < instance->objetNb; i++){
        intermediaire[i] = i+1;
    }

    for(int i=0; i < instance->objetNb; i++){
        tab[i] = intermediaire[rand() % (instance->objetNb - (i))];
        retraitElemTab(&intermediaire,instance->objetNb-(i),tab[i]);
    }
    free(intermediaire);
}

/** Remplit un tableau avec une permutation d'objets de valeur décroissante
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decValPick(int* tab, Instance *instance){
    int * valeurs = (int*)malloc( (instance->objetNb) * sizeof(int));
    memcpy(valeurs, instance->Pj, instance->objetNb*sizeof(int));

    for(int i=0; i < instance->objetNb; i++){
        tab[i] = i+1;
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = instance->objetNb;
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
                tmpVal = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(valeurs);
}

/** Remplit un tableau avec une permutation d'objets avec un ratio valeur/sommedespoids décroissant
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decRatioValPoidsPick(int* tab, Instance *instance){
    double * ratios = (double*)malloc( (instance->objetNb) * sizeof(double));

    for(int i=0; i < instance->objetNb; i++){
        int sommePoids = 0;
        for(int j=0; j < instance->dimensionNb; j++){
            sommePoids += instance->Rij[j][i];
        }
        ratios[i] = instance->Pj[i]/(double)sommePoids;
    }

    for(int i=0; i < instance->objetNb; i++){
        tab[i] = i+1;
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = instance->objetNb;
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
                tmpVal = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(ratios);
}

/** Remplit un tableau avec une permutation d'objets avec un ratio valeur/sommedespoids sur la dimension critique décroissant
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decRatioValPoidsCritPick(int* tab, int tailleTab, Instance *instance, int *etatDimensions){
    double * ratios = (double*)malloc( (tailleTab) * sizeof(double));
    int dimensionCritique = 0;

    if(etatDimensions == NULL){
        int poidsMin = instance->Bi[0];
        for(int i=1; i < instance->dimensionNb; i++){
            if(instance->Bi[i] < poidsMin){
                poidsMin = instance->Bi[i];
                dimensionCritique = i;
            }
        }

        for(int i=0; i < tailleTab; i++){
            tab[i] = i+1;
        }
    }
    else{
        int poidsMin = etatDimensions[0];
        for(int i=1; i < instance->dimensionNb; i++){
            if(etatDimensions[i] < poidsMin){
                poidsMin = etatDimensions[i];
                dimensionCritique = i;
            }
        }
    }

    for(int i=0; i < tailleTab; i++){
        ratios[i] = instance->Pj[tab[i]-1]/(double)instance->Rij[dimensionCritique][tab[i]-1];
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = tailleTab;
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
                tmpVal = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(ratios);
}

/** Remplit un tableau avec une permutation d'objets en fonction du ratio valeur/(moyennePoids + ecartType) de chaque objet
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void ratioValMoyPoids(int* tab, int tailleTab, Instance *instance){

    double * ratios = (double*)malloc( (tailleTab) * sizeof(double));
    double moyCourante = 0;
    double varianceCourante = 0;
    double moyET[instance->objetNb][2] ; //stock du poids moyen et de l'ecart type des objets


    for(int i = 0; i < instance->objetNb; i++){

        for(int j = 0; j<instance->dimensionNb; j++){
            moyCourante += instance->Rij[i][j];     //calcul de la somme des poids de chaque dimension de l'objet
        }

        moyET[i][0] = moyCourante/instance->dimensionNb; //division pour passer à la moyenne

        for(int j = 0; j<instance->dimensionNb; j++){
            varianceCourante += (instance->Rij[i][j] - moyCourante) * (instance->Rij[i][j] - moyCourante); //calcul de la variance sans la division
        }
        varianceCourante = varianceCourante/instance->dimensionNb;      //division de la variance
        moyET[i][1] = sqrt(varianceCourante);       //passage de variance à ecart type

        moyCourante = 0;
        varianceCourante = 0;
    }

    for(int i=0; i < tailleTab; i++){
        tab[i] = i+1;   //Numérotation de chaque objet de l'instance
    }


    for(int i=0; i < tailleTab; i++){
        ratios[i] = instance->Pj[tab[i]-1]/(moyET[i][0] + moyET[i][1]);
    }

    //Tri à bulle
    int enOrdre = 0;
    int taille = tailleTab;
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
                tmpVal = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = tmpVal;
                enOrdre = 0;
            }
        }
        taille--;
    }

    free(ratios);

}

/** Heuristique indirecte
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void Indirect(int* tab, Instance *instance, int typeOrdonnancement){

    int * solutionInd = (int*)malloc( (instance->objetNb) * sizeof(int));

    memset(tab,0,instance->objetNb*sizeof(int));

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
        decRatioValPoidsCritPick(solutionInd, instance->objetNb, instance, NULL);
        break;
    case 5:
        //Stratégie d'ordonnancement à développer
        break;
    }

    decode(solutionInd,tab,instance);
    free(solutionInd);
}

/** Heuristique directe
 * @param tab le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void Direct(int* tab, Instance *instance, int typeOrdonnancement){
    int * solutionInd = (int*)malloc( (instance->objetNb) * sizeof(int));
    int * solutionIndFirst = solutionInd;
    int *sommePoids = calloc(instance->dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension
    int *etatDimensions = calloc(instance->dimensionNb,sizeof(int)); //La somme de valeurs pour chaque dimension

    memset(tab,0,instance->objetNb*sizeof(int));

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
        decRatioValPoidsCritPick(solutionInd, instance->objetNb, instance, NULL);
        break;
    case 5:
        ratioValMoyPoids(solutionInd, instance->objetNb, instance);
        break;
    case 6: //Ratio valeur/poids mis à jour
        decRatioValPoidsCritPick(solutionInd, instance->objetNb, instance, NULL);
        for(int i=0;i<instance->dimensionNb;i++)
            etatDimensions[i] = instance->Bi[i];
        break;
    }

    for(int i=0;i<instance->objetNb;i++){
        int resultTest = 0;

        for(int j=0; j<instance->dimensionNb; j++){
            if(sommePoids[j]+instance->Rij[j][*solutionInd-1] <= instance->Bi[j]){
                resultTest++;
            }
            else{
                break;
            }
        }

        if(resultTest == instance->dimensionNb){
            for(int j=0; j<instance->dimensionNb; j++){
                sommePoids[j]+=instance->Rij[j][*solutionInd-1];
            }
            tab[*solutionInd-1] = 1;

            if(typeOrdonnancement == 6){
                for(int i=0;i<instance->dimensionNb;i++){
                    etatDimensions[i] -= instance->Rij[i][*solutionInd-1];
                }
            }
        }

        solutionInd++; //Equivaut à supprimer le premier élément du tableau

        if(typeOrdonnancement == 6){
            decRatioValPoidsCritPick(solutionInd, instance->objetNb-i-1, instance, etatDimensions);
        }

    }
    free(sommePoids);
    free(solutionIndFirst);
    free(etatDimensions);
}
