#include "instance.h"

/**
    Retourne une instance crée sur le tas
    Préconditions : Ligne d'entrée non nulle
**/

Instance * Instance_createInstance(FILE *instanceFile){
    //Instance *yolo = malloc(sizeof(Instance));
    char *line;
    while((line = readLine(instanceFile)) != NULL){
        printf("%s",line);
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
