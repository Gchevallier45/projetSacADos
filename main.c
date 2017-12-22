#include "instance.h"
#include "timer.h"
#include "codage.h"

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

    int *solution=calloc(grInstances->instances[0].objetNb,sizeof(int));//malloc(sizeof(int)*instance.objetNb);
    int *tabAlea = (int*)malloc((grInstances->instances[0].objetNb) * sizeof(int));

    randPick(tabAlea,grInstances->instances[0]);
    decode(tabAlea,grInstances->instances[0].objetNb,solution,grInstances->instances[0]);
    free(tabAlea);
    free(solution);
    affSoluce(grInstances->instances[0].sol1);
    writeSoluce(grInstances->instances[0].sol1);
    InstanceTableau_videDetruire(grInstances);

    return 0;
}
