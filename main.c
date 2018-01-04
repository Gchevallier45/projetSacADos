#include "instance.h"
#include "timer.h"
#include "codage.h"
#include "heuristique.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
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

    unsigned long long solutionMoyenne = 0;

    for(int y=0;y<10;y++){
    time_t time1000 = timer_start();
    for(int x=0;x<1000;x++){
    int *tabAlea = (int*)malloc((grInstances->instances[0].objetNb) * sizeof(int));

    Indirect(tabAlea,grInstances->instances[0],1);

    solutionMoyenne += directResultat(tabAlea,grInstances->instances[0].Pj,grInstances->instances[0].objetNb);
    //printf("FOUND : %d (MAX POSSIBLE : %d)\n",directResultat(tabAlea,grInstances->instances[0].Pj,grInstances->instances[0].objetNb),grInstances->instances[0].sol1);
    //printf("%lld",solutionMoyenne);
    free(tabAlea);
    }

    printf("TOTAL TIME : %f \n",timer_getTime(time1000));
    }
    printf("--------------------------------------------------------------------\n");
    printf("Solution moyenne : %d, soit %.4f%% de la meilleure solution %d\n",solutionMoyenne/10000,((float)(solutionMoyenne/10000)/grInstances->instances[0].sol1)*100,grInstances->instances[0].sol1);

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
