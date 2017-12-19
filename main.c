#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instance.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    time_t timer;
    timer = timer_start();
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
    InstanceTableau *instances = InstanceTableau_initCreer();

    if(file != NULL){
        InstanceTableau_remplirInstances(instances,file);
        fclose(file);
    }
    else{
        printf("FATAL ERROR : FILE NOT FOUND\n");
    }

    InstanceTableau_videDetruire(instances);


    printf("TIME : %lfs\n",timer_getTime(timer));

    return 0;
}
