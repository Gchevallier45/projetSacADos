#include "instance.h"
#include "timer.h"
#include "codage.h"
#include "heuristique.h"
#include "metaheuristique.h"
#include "genetique.h"

//Opti pour déplacer tableau (c'est des tests pour l'algo génétique)
int main2(){
    int *tab = malloc(2048*sizeof(int));
    for(int i=0;i<2048;i++)
        tab[i] = i;
    for(int k=0;k<100000;k++){
                for(int j=0;j<100000;j++){
                        /*for(int i=0;i<2047;i++){
                                tab[i]=tab[i+1];
    }*/
    memmove(tab,tab+1,2047*sizeof(int));
    }
    printf("%d\n",k);
    //affSoluce(tab,2048);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //core(argc,argv);

    Parameters p;
    p.filePath = argv[1];
    p.code = argv[2];
    p.method = argv[3];

    printf("Filepath : %s \n",p.filePath);
    printf("Code : %s \n",p.code);
    printf("Method : %s \n",p.method);

    char dest[1024];
    strcpy(dest,p.filePath);
    //strcat(dest,"/_mknapcb1_res.txt");
    //printf("%s\n",dest);

    FILE *file = fopen("/home/etudiant/Desktop/MKP-Instances/_mknapcb1_res.txt","r");
    //FILE *file = fopen(dest,"r");
    InstanceTableau *grInstances = InstanceTableau_initCreer();

    if(file != NULL){
        InstanceTableau_remplirInstances(grInstances,file);
        fclose(file);
    }
    else{
        printf("FATAL ERROR : FILE NOT FOUND\n");
    }

    /*int *testtab = malloc(100*sizeof(int));
    for(int i=0; i<100;i++)
        testtab[i] = 1;
    printf("RESULTAT : %d",directFaisable(grInstances->instances[0].Xj,&grInstances->instances[0]));*/

    benchValgrind(&grInstances->instances[0]);

    double moyennePourcentage = 0;
    printf("INSTANCE | TEMPS CALCUL | %% SOLUTION | SOLUTION | SOLUTION MAX \n");
    for(int i=0; i<grInstances->instancesNb; i++){
        time_t time1000 = timer_start();
        printf("   %.2d    |",i+1);
        int *tabAlea = (int*)malloc((grInstances->instances[i].objetNb) * sizeof(int));
        Direct(tabAlea,&grInstances->instances[i],1);
        //metaLocalIndirecte(tabAlea,&grInstances->instances[i]);

        metaTabouIndirecte(tabAlea, &grInstances->instances[i], 1000, 65, 1);


        //metaTabouDirecte(tabAlea,&grInstances->instances[i],75,1,75);

        //metaGenetiqueIndirecte(tabAlea,&grInstances->instances[i],100,30,50);

        //metaLocalDirecte(tabAlea,&grInstances->instances[i]);

        int resultat = directResultat(tabAlea,&grInstances->instances[i]);

        double time = timer_getTime(time1000);

        printf("   %f   |   %.2f%%   |  %d   |   %d     \n",time,100*(resultat/(double)grInstances->instances[i].sol1),resultat,grInstances->instances[i].sol1);
        timeFile(i+1,resultat,time);

        free(tabAlea);
        moyennePourcentage += 100*(resultat/(double)grInstances->instances[i].sol1);

        //i=grInstances->instancesNb;
    }
    printf("\n              | QUALITE SOLUTIONS --> %.2f%% |\n\n",moyennePourcentage/grInstances->instancesNb);

    /*affSoluce(grInstances->instances[0].sol1);
    writeSoluce(grInstances->instances[0].sol1);*/
    InstanceTableau_videDetruire(grInstances);

    return 0;
}

void benchValgrind(Instance *instance){
    int *tabAlea = (int*)malloc((instance->objetNb) * sizeof(int));
    printf("test valgrind... |");
    printf("0%%---");
    fflush(stdout);
    for(int i=1;i<=6;i++){
        if(i!=5){
            Direct(tabAlea,instance,i);
            if(i!=6)
                Indirect(tabAlea,instance,i);
        }
    }
    printf("5%%---");
    fflush(stdout);
    metaLocalDirecte(tabAlea,instance);
    printf("10%%---");
    fflush(stdout);
    metaLocalIndirecte(tabAlea,instance);
    printf("20%%---");
    fflush(stdout);
    metaTabouDirecte(tabAlea,instance,30,1,10);
    printf("30%%---");
    fflush(stdout);
    metaTabouIndirecte(tabAlea,instance,30,10,1);
    printf("40%%---");
    fflush(stdout);
    metaGenetiqueDirecte(tabAlea,instance,10,50,50);
    printf("60%%---");
    fflush(stdout);
    metaGenetiqueIndirecte(tabAlea,instance,10,50,50);
    printf("100%%|");
    fflush(stdout);
    free(tabAlea);
    printf("\n");
}
