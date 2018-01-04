#include "heuristique.h"

/** Retourne une liste d'objets initialisée créé sur le tas
 * @return un pointeur sur une liste d'objets
 */
ListeObjets * ListeObjets_initCreer(){
    ListeObjets * tmp = malloc(sizeof(ListeObjets));
    tmp->objet = 0;
    tmp->suivant = NULL;
    return tmp;
}

/** Vide et détruit une liste d'objets initialisée créé sur le tas
 * @param listeObjets un pointeur sur une structure de type ListeObjets
 */
void ListeObjets_videDetruire(ListeObjets * listeObjets){
    ListeObjets *tmp = listeObjets;
    while(tmp != NULL){
        free(tmp);
        tmp = tmp->suivant;
    }
    //free(listeObjets);
}

/** Insère un objet à la suite de la liste
 * @param listeObjets un pointeur sur une structure de type ListeObjets
 * @param numeroObjet le numero de l'objet à ajouter et à insérer dans la liste
 */
void ListeObjets_insererObjet(ListeObjets ** listeObjets, ListeObjets * objet){
    if(*listeObjets == NULL){
        *listeObjets = objet;
    }
    else{
        ListeObjets *current = *listeObjets;
        while(current->suivant != NULL)
            current = current->suivant;

        current->suivant = objet;
    }
}

/** Supprime un objet de la liste
 * @param listeObjets un pointeur sur une structure de type ListeObjets
 * @param objet l'objet à supprimer de la liste
 */
void ListeObjets_supprimerObjet(ListeObjets ** listeObjets, ListeObjets * objet) {
    ListeObjets *before = *listeObjets;

    while(before != NULL && before->suivant != objet)
        before = before->suivant;

    if(before != NULL){
        before->suivant=objet->suivant;
    }
    else{
        *listeObjets = objet->suivant;
    }
}

/** Obtenir l'objet à l'indice
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */
ListeObjets * ListeObjets_obtenirObjet(ListeObjets * listeObjets, int objetIndex) {
    if(objetIndex < 0)
        return NULL;
    int i=0;
    ListeObjets *res = listeObjets;
    while(i<objetIndex && res!=NULL){
        ++i;
        res=res->suivant;
    }
    return res;
}

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
}

/** Remplit un tableau avec une permutation d'objets de valeur décroissante
 * @param tabAlea le tableau dans lequel sera stocké la permutation
 * @param instance l'instance à utiliser pour générer la permutation
 * Préconditions : tabAlea non nul, et d'une taille correspondant au nombre d'objets de la permutation
 */
void decValPick(int* tabAlea, Instance instance){
    //int * intermediaire = (int*)malloc( (instance.objetNb) * sizeof(int));
    int * valeurs = (int*)malloc( (instance.objetNb) * sizeof(int));
    memcpy(valeurs, instance.Pj, instance.objetNb*sizeof(int));

    for(int i=0; i < instance.objetNb; i++){
        tabAlea[i] = i;
    }

    /*for(int i=0; i < instance.objetNb; i++){
        tabAlea[i] = intermediaire[rand() % (instance.objetNb - (i))];
        retraitElemTab(&intermediaire,instance.objetNb-(i),tabAlea[i]);
    }*/

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

    //affSoluce(valeurs,instance.objetNb);

    free(valeurs);
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
    }
    //randPick(solutionInd, instance);
    //decValPick(solutionInd, instance);
    decode(solutionInd,instance.objetNb,tabAlea,instance);
    free(solutionInd);

    /*ListeObjets *liste = ListeObjets_initCreer();
    ListeObjets *current = liste;

    for(int i=0; i < instance.objetNb; i++){
        ListeObjets *tmp = ListeObjets_initCreer();
        tmp->objet = i;
        tmp->suivant = NULL;
        ListeObjets_insererObjet(&current,tmp);
        current = tmp;
    }

    current = liste;
    int lastRand = 0;
    for(int i=0; i < instance.objetNb; i++){
        int randNb = rand() % (instance.objetNb - (i));
        if(randNb>=lastRand){
            ListeObjets *insert = ListeObjets_obtenirObjet(current,randNb-lastRand);
            tabAlea[i] = insert->objet;
            ListeObjets_supprimerObjet(&current,insert);
            current = insert->suivant;
        }
        else{
            ListeObjets *insert = ListeObjets_obtenirObjet(liste,randNb);
            tabAlea[i] = insert->objet;
            ListeObjets_supprimerObjet(&liste,insert);
            current = insert->suivant;
        }
        lastRand = randNb;
    }

    ListeObjets_videDetruire(liste);*/
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

    for(int i=0;i<instance.objetNb;i++)
        tabAlea[i] = 0;

    switch(typeOrdonnancement){
    case 1:
        randPick(solutionInd, instance);
        break;
    case 2:
        decValPick(solutionInd, instance);
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
        }

        solutionInd++; //Equivaut à supprimer le premier élément du tableau
    }
    free(sommePoids);
    free(solutionIndFirst);
}
