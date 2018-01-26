#include "instance.h"
#include "timer.h"
#include "codage.h"
#include "heuristique.h"
#include "metaheuristique.h"
#include "genetique.h"

/* DEFINITION DES PARAMETRES A PASSER AU PROGRAMME
    1 : chemin du fichier
    2 : type de codage (1 pour direct, 2 pour indirect)
    3 : type de méthode de résolution (1 pour heuristique, 2 pour métaheuristique)
    4 : paramètre de la méthode de résolution (type d'heuristique ou de metaheuristique)
*/

/** Fonction de test pour Valgrind
 * Permet de lancer tout nos algorithmes pour tester les fuites mémoires
 */
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
    metaTabouDirecte(tabAlea,instance,20,1,10);
    printf("30%%---");
    fflush(stdout);
    metaTabouIndirecte(tabAlea,instance,20,10,1);
    printf("40%%---");
    fflush(stdout);
    metaGenetiqueDirecte(tabAlea,instance,10,20,50);
    printf("60%%---");
    fflush(stdout);
    metaGenetiqueIndirecte(tabAlea,instance,10,20,50);
    printf("100%%|");
    fflush(stdout);
    free(tabAlea);
    printf("\n");
}

/** Interface pour les paramètres et les méthodes de calcul
 * @param param la structure contenant les paramètres passés au programme
 * @param solution le tableau dans lequel stocker la solution
 * @param instance l'instance correspondant au problème à traiter
 */
void interface(Parametres param, int *solution, Instance *instance){
    if(param.methode == HEURISTIQUE){ //Heuristiques
        if(param.codage == CODAGEDIRECT)
            Direct(solution,instance,param.paramMethode);
        else if(param.codage == CODAGEINDIRECT)
            Indirect(solution,instance,param.paramMethode);
    }
    else if(param.methode == METAHEURISTIQUE){ // Metaheuristiques
        switch(param.paramMethode){
            case 1: //Metaheuristique locale
                if(param.codage == CODAGEDIRECT)
                    metaLocalDirecte(solution,instance);
                else if(param.codage == CODAGEINDIRECT)
                    metaLocalIndirecte(solution,instance);
                break;
            case 2: //Metaheuristique tabou
                if(param.codage == CODAGEDIRECT)
                    metaTabouDirecte(solution,instance,100,1,100);
                else if(param.codage == CODAGEINDIRECT)
                    metaTabouIndirecte(solution,instance,100,100,1);
                break;
            case 3: //Metaheuristique genetique
                if(param.codage == CODAGEDIRECT)
                    metaGenetiqueDirecte(solution,instance,100,300,50);
                else if(param.codage == CODAGEINDIRECT)
                    metaGenetiqueIndirecte(solution,instance,100,300,50);
                break;
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Parametres p;
    p.cheminFichier = argv[1];
    p.codage = atoi(argv[2]);
    p.methode = atoi(argv[3]);
    p.paramMethode = atoi(argv[4]);

    printf("Chemin du fichier : %s \n",p.cheminFichier);
    printf("Type de codage : %d \n",p.codage);
    printf("Méthode : %d \n",p.methode);
    printf("Paramètres de la méthode : %d \n",p.paramMethode);

    char dest[1024];
    strcpy(dest,p.cheminFichier);

    FILE *file = fopen(dest,"r");
    InstanceTableau *grInstances = InstanceTableau_initCreer();

    if(file != NULL){
        InstanceTableau_remplirInstances(grInstances,file);
        fclose(file);
    }
    else{
        printf("FATAL ERROR : FILE NOT FOUND\n");
    }

    benchValgrind(&grInstances->instances[0]);

    double moyennePourcentage = 0;
    printf("INSTANCE | TEMPS CALCUL | %% SOLUTION | SOLUTION | SOLUTION MAX \n");
    for(int i=0; i<grInstances->instancesNb; i++){
        time_t time1000 = timer_start();
        printf("   %.2d    |",i+1);
        int *tabAlea = (int*)malloc((grInstances->instances[i].objetNb) * sizeof(int));

        interface(p,tabAlea,&grInstances->instances[i]);

        int resultat = directResultat(tabAlea,&grInstances->instances[i]);

        double time = timer_getTime(time1000);

        printf("   %f   |   %.2f%%   |  %d   |   %d     \n",time,100*(resultat/(double)grInstances->instances[i].sol1),resultat,grInstances->instances[i].sol1);
        timeFile(i+1,resultat,time);

        free(tabAlea);
        moyennePourcentage += 100*(resultat/(double)grInstances->instances[i].sol1);
    }
    printf("\n              | QUALITE SOLUTIONS --> %.2f%% |\n\n",moyennePourcentage/grInstances->instancesNb);

    InstanceTableau_videDetruire(grInstances);

    return 0;
}
