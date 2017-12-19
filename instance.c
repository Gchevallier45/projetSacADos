#include "instance.h"

/**
  * Retourne un tableau d'instances initialisé créé sur le tas
**/
InstanceArray * InstanceArray_initAndCreate(){
    InstanceArray * tmp = malloc(sizeof(InstanceArray));
    tmp->instances = NULL;
    tmp->numberOfInstances = 0;
    return tmp;
}

/**
  * Vide et détruit un tableau d'instances créé sur le tas
**/
void InstanceArray_finalizeAndDestroy(InstanceArray *instanceArray){
    for(int i=0; i<instanceArray->numberOfInstances; i++){
        free(instanceArray->instances[i].Bi);
        free(instanceArray->instances[i].Pj);
        free(instanceArray->instances[i].Xj);
        for(int j=0; j<instanceArray->instances[i].dimensionNb; j++)
            free(instanceArray->instances[i].Rij[j]);
        free(instanceArray->instances[i].Rij);
    }
    free(instanceArray->instances);
    free(instanceArray);
}

/**
 *  Retourne un tableau d'instances créées sur le tas
 *  Préconditions : Ligne d'entrée non nulle
**/
void InstanceArray_fillInstances(InstanceArray *instanceArray, FILE *instanceFile){
    char *line = NULL;
    char *pEnd = line;

    line = readLine(instanceFile);
    pEnd = line;
    instanceArray->numberOfInstances = (int)strtol(pEnd,&pEnd,10);
    instanceArray->instances = (Instance*)malloc(sizeof(Instance)*instanceArray->numberOfInstances);
    free(line);

    //On saute une ligne du fichier
    line=readLine(instanceFile);
    free(line);

    for(int i=0; i<instanceArray->numberOfInstances; i++){
        Instance *currentInstance = &instanceArray->instances[i];

        //On saute les deux lignes qui séparent chaque instance
        for(int j=0; j<2; j++){
            line=readLine(instanceFile);
            free(line);
        }

        //On lit les informations de l'instance
        line=readLine(instanceFile); //Ligne qui contient le nombre d’objet N, le nombre de dimension M, les valeurs connues de solutions trouvée
        //Lecture des premiers paramètres de l'instance
        pEnd = line;
        for(int j=0; j<4; j++){
            switch (j){
            case 0:
                currentInstance->objectNb = (int)strtol(pEnd,&pEnd,10);
                break;
            case 1:
                currentInstance->dimensionNb = (int)strtol(pEnd,&pEnd,10);
                break;
            case 2:
                currentInstance->sol1 = (int)strtol(pEnd,&pEnd,10);
                break;
            case 3:
                currentInstance->sol2 = (int)strtol(pEnd,&pEnd,10);
                break;
            }
        }
        free(line);

        //Lecture des variables Xj
        line=readLine(instanceFile);
        pEnd = line;
        currentInstance->Xj = malloc(sizeof(int)*currentInstance->objectNb);
        for(int j=0; j<currentInstance->objectNb; j++){
            currentInstance->Xj[j] = (int)strtol(pEnd,&pEnd,10);
        }
        free(line);

        //On saute une ligne
        line=readLine(instanceFile);
        free(line);

        //Lecture des variables Pj
        line=readLine(instanceFile);
        pEnd = line;
        currentInstance->Pj = malloc(sizeof(int)*currentInstance->objectNb);
        for(int j=0; j<currentInstance->objectNb; j++){
            currentInstance->Pj[j] = (int)strtol(pEnd,&pEnd,10);
        }
        free(line);

        //On saute une ligne
        line=readLine(instanceFile);
        free(line);

        //Lecture des poids Rij pour chaque dimension
        currentInstance->Rij = (int**)malloc(sizeof(int*)*currentInstance->dimensionNb);
        for(int k=0; k<currentInstance->dimensionNb; k++){
            line=readLine(instanceFile);
            pEnd = line;
            currentInstance->Rij[k] = (int*)malloc(sizeof(int)*currentInstance->objectNb);
            for(int j=0; j<currentInstance->objectNb; j++){
                currentInstance->Rij[k][j] = (int)strtol(pEnd,&pEnd,10);
            }
            free(line);
        }

        //On saute une ligne
        line=readLine(instanceFile);
        free(line);

        //Lecture des variables Bi
        line=readLine(instanceFile);
        pEnd = line;
        currentInstance->Bi = (int*)malloc(sizeof(int)*currentInstance->dimensionNb);
        for(int j=0; j<currentInstance->dimensionNb; j++){
            currentInstance->Bi[j] = (int)strtol(pEnd,&pEnd,10);
        }
        free(line);
    }
    printf("Fichier parsé avec succès\n");
}

/** Lit une ligne d'un fichier
**/
char* readLine(FILE *file){
    char *p = NULL;
    char buf[1024];
    if(fgets(buf,sizeof(buf),file) != NULL)
        p = strdup(buf);
    return p;
}
