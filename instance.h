#include <stdio.h>

typedef struct _Parameters{
    char* filePath;
    char* code;
    char* method;
} Parameters;

typedef struct _Instance{
    int objectNb;
    int dimansionNb;
    int sol1;
    int sol2;
} Instance;

Instance * Instance_createInstance(FILE *instanceFile);

char* readLine(FILE *file);
