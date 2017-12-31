#include "instance.h"
#include "timer.h"
#include "codage.h"
#include "heuristique.h"

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

    FILE *file = fopen("/home/etudiant/Desktop/MKP-Instances/_mknapcb3_res.txt","r");
    InstanceTableau *grInstances = InstanceTableau_initCreer();

    if(file != NULL){
        InstanceTableau_remplirInstances(grInstances,file);
        fclose(file);
    }
    else{
        printf("FATAL ERROR : FILE NOT FOUND\n");
    }
    //printf("SOLUTION : %d \n",directResultat(instances->instances[0].Xj,instances->instances[0].Pj,instances->instances[0].objetNb));

    for(int y=0;y<10;y++){
    time_t time1000 = timer_start();
    for(int x=0;x<1000;x++){
    int *tabAlea = (int*)malloc((grInstances->instances[0].objetNb) * sizeof(int));

    //randPick(tabAlea,grInstances->instances[0]);
    Indirect_aleat(tabAlea,grInstances->instances[0]);
    free(tabAlea);
    }

    printf("TOTAL TIME : %f \n",timer_getTime(time1000));
    }

    /*for(int x=0;x<10;x++){
    time_t time1000 = timer_start();
    for(int i=0; i<1000000; i++){
    int *solution=calloc(grInstances->instances[0].objetNb,sizeof(int));//malloc(sizeof(int)*instance.objetNb);

    decode(tabAlea,grInstances->instances[0].objetNb,solution,grInstances->instances[0]);
    free(solution);
        free(tabAlea);
    }
    printf("TOTAL TIME : %f \n",timer_getTime(time1000));
    }
    affSoluce(grInstances->instances[0].sol1);
    writeSoluce(grInstances->instances[0].sol1);*/
    InstanceTableau_videDetruire(grInstances);

    return 0;
}
