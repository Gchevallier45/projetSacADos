#include "instance.h"

/**
    Retourne un tableau d'instances créées sur le tas
    Préconditions : Ligne d'entrée non nulle
**/

Instance ** Instance_createInstances(Instance *instanceStructure[30], FILE *instanceFile){

    char *line;
    int numberLine = 0;
    int instanceIndice = 0;
    while((line = readLine(instanceFile)) != NULL){
        //printf("%s",line);
        instanceStructure[instanceIndice]=malloc(sizeof(Instance));
        if(numberLine == 0){
            char *pEnd;
            //instanceReturned[instanceIndice]->objectNb = (int)strtol(line,pEnd,10);
            numberLine++;
        }
        free(line);
        break;
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
