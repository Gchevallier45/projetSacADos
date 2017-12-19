#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instance.h"
#include "timer.h"




void core(int argc, char *argv[]){
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
    InstanceArray *instances = InstanceArray_initAndCreate();

    if(file != NULL){
        InstanceArray_fillInstances(instances,file);
        fclose(file);
    }
    else{
        printf("/!\\ FATAL ERROR : FILE NOT FOUND /!\\ \n");
    }

    InstanceArray_finalizeAndDestroy(instances);
}

int main(int argc, char *argv[])
{
    time_t timer;

    timer = timer_start();
    core(argc,argv);
    //sleep(1);
    //printf("TIME : %lfs\n",timer_getTime(timer));

    /*for(int i=0; i<1000000;i++){
            for(int j=0; j<1000;j++){}
    }*/

    printf("TIME : %lfs\n",timer_getTime(timer));

    //FILE *file = fopen(dest,"r");

    //printf("Hello world!\n");

    return 0;
}
