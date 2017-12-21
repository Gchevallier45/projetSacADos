#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instance.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    //core(argc,argv);

    /*Parameters p;
    p.filePath = argv[1];
    p.code = argv[2];
    p.method = argv[3];

    printf("Filepath : %s \n",p.filePath);
    printf("Code : %s \n",p.code);
    printf("Method : %s \n",p.method);

    char dest[1024];
    strcpy(dest,p.filePath);
    strcat(dest,"/_mknapcb1_res.txt");
    printf("%s\n",dest);*/

    FILE *file = fopen("/home/etudiant/Desktop/MKP-Instances/_mknapcb1_res.txt","r");
    InstanceTableau *grInstances = InstanceTableau_initCreer();

    if(file != NULL){
        InstanceTableau_remplirInstances(grInstances,file);
        fclose(file);
    }
    else{
        printf("FATAL ERROR : FILE NOT FOUND\n");
    }
    //printf("SOLUTION : %d \n",directResultat(instances->instances[0].Xj,instances->instances[0].Pj,instances->instances[0].objetNb));
    affSoluce(grInstances->instances->sol1);
    InstanceTableau_videDetruire(grInstances);

    return 0;
}
