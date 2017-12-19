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
    int *objects;
} Instance;

typedef struct _InstanceArray{
    Instance *instances;
    int numberOfInstances;
} InstanceArray;

InstanceArray * InstanceArray_initAndCreate();
InstanceArray * InstanceArray_fillInstances(InstanceArray *instanceArray, FILE *instanceFile);

char* readLine(FILE *file);
