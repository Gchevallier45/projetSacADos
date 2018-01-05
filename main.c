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

    double moyennePourcentage = 0;
    printf("INSTANCE | TEMPS CALCUL | %% SOLUTION | SOLUTION | SOLUTION MAX \n");
    for(int i=0; i<grInstances->instancesNb; i++){
        time_t time1000 = timer_start();
        printf("   %.2d    |",i+1);
        int *tabAlea = (int*)malloc((grInstances->instances[i].objetNb) * sizeof(int));
        Direct(tabAlea,grInstances->instances[i],3);
        printf("   %f   |",timer_getTime(time1000));
        int resultat = directResultat(tabAlea,grInstances->instances[i].Pj,grInstances->instances[i].objetNb);
        printf("   %.2f%%   |",100*(resultat/(double)grInstances->instances[i].sol1));//,resultat,grInstances->instances[i].sol1);
        printf("  %d   |",resultat);
        printf("   %d     \n",grInstances->instances[i].sol1);
        free(tabAlea);
        moyennePourcentage += 100*(resultat/(double)grInstances->instances[i].sol1);
    }
    printf("\n              | QUALITE SOLUTIONS --> %.2f%% |\n\n",moyennePourcentage/grInstances->instancesNb);
    /*affSoluce(grInstances->instances[0].sol1);
    writeSoluce(grInstances->instances[0].sol1);*/
    InstanceTableau_videDetruire(grInstances);

    return 0;
}
