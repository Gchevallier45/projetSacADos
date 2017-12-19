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

    char *line;
    //On saute les 4 premières lignes du fichier
    for(int j=0; j<2; j++){
        line=readLine(instanceFile);
        free(line);
    }

    for(int i=0; i<30; i++){
        //instanceStructure[i]=malloc(sizeof(Instance));

        //On saute les deux lignes qui séparent chaque instance
        for(int j=0; j<2; j++){
            line=readLine(instanceFile);
            free(line);
        }

        //On lit les informations de l'instance
        line=readLine(instanceFile); //Ligne qui contient le nombre d’objet N, le nombre de dimension M, les valeurs connues de solutions trouvée
        char *splittedString = strdup(line); //strsep(&line," ");
        printf("%s\n",line);

        //if(numberLine == 0){
            //char *pEnd;
            //instanceReturned[instanceIndice]->objectNb = (int)strtol(line,pEnd,10);
            //numberLine++;
        //}
        free(line);
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
