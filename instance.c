#include "instance.h"

/**
  * Retourne un tableau d'instances initialisé créé sur le tas
**/
InstanceArray * InstanceArray_initAndCreate(){
    InstanceArray * tmp = malloc(sizeof(InstanceArray));
    tmp->numberOfInstances = 0;
    return tmp;
}

/**
 *  Retourne un tableau d'instances créées sur le tas
 *  Préconditions : Ligne d'entrée non nulle
**/
InstanceArray * InstanceArray_fillInstances(InstanceArray *instanceArray, FILE *instanceFile){

    char *line = NULL;
    char *pEnd = NULL;

    line = readLine(instanceFile);
    instanceArray->numberOfInstances = (int)strtol(line,pEnd,10);
    instanceArray->instances = (Instance*)malloc(sizeof(Instance)*instanceArray->numberOfInstances);
    free(line);

    //On saute une ligne du fichier
    line=readLine(instanceFile);
    free(line);

    for(int i=0; i<instanceArray->numberOfInstances; i++){
        Instance currentInstance = instanceArray->instances[i];

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
                currentInstance.objectNb = (int)strtol(pEnd,&pEnd,10);
                break;
            case 1:
                currentInstance.dimensionNb = (int)strtol(pEnd,&pEnd,10);
                break;
            case 2:
                currentInstance.sol1 = (int)strtol(pEnd,&pEnd,10);
                break;
            case 3:
                currentInstance.sol2 = (int)strtol(pEnd,&pEnd,10);
                break;
            }
        }
        //printf("SOL2 : %d\n",currentInstance.sol2);
        free(line);

        //Lecture des variables Xj
        line=readLine(instanceFile);
        pEnd = line;
        currentInstance.objects = malloc(sizeof(int)*currentInstance.objectNb);
        for(int j=0; j<currentInstance.objectNb; j++){
            currentInstance.objects[i] = (int)strtol(pEnd,&pEnd,10);
        }
        free(line);

        //On saute une ligne
        line=readLine(instanceFile);
        free(line);

        //

        //if(numberLine == 0){
            //char *pEnd;
            //instanceReturned[instanceIndice]->objectNb = (int)strtol(line,pEnd,10);
            //numberLine++;
        //}
        //free(line);
        i=30;
    }
    return NULL;
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
