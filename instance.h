#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Parameters{
    char* filePath;
    char* code;
    char* method;
} Parameters;

typedef struct _Instance{
    int objectNb;
    int dimensionNb;
    int sol1;
    int sol2;
    int *Xj; //Les variables Xj des solutions trouvées
    int *Pj; //La valeur des objets
    int *Bi; //Poids à ne pas dépasser pour chaque dimension
    int **Rij; //Pour chaque dimension la valeur des poids
} Instance;

typedef struct _InstanceArray{
    Instance *instances;
    int numberOfInstances;
} InstanceArray;


InstanceArray * InstanceArray_initAndCreate();

void InstanceArray_finalizeAndDestroy(InstanceArray *instanceArray);

void InstanceArray_fillInstances(InstanceArray *instanceArray, FILE *instanceFile);

char* readLine(FILE *file);
