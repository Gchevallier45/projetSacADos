#include "instance.h"

/**
    Retourne une instance crée sur le tas
    Préconditions : Ligne d'entrée non nulle
**/

Instance * Instance_createInstance(FILE *instanceFile){
    Instance *instanceReturned = malloc(sizeof(Instance));
    char *line;
    int numberLine = 0;
    while((line = readLine(instanceFile)) != NULL){
        //printf("%s",line);
        if(numberLine == 0){
            char *pEnd;
            instanceReturned->objectNb = strtol(line,pEnd,10);
            numberLine++;
        }
        free(line);
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
