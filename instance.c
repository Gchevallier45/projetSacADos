#include "instance.h"

/** Retourne un tableau d'instances initialisé créé sur le tas
 * @return un pointeur sur un tableau d'instances
 */
InstanceTableau * InstanceTableau_initCreer(){
    InstanceTableau * tmp = malloc(sizeof(InstanceTableau));
    tmp->instances = NULL;
    tmp->instancesNb = 0;
    return tmp;
}

/** Vide et détruit un tableau d'instances créé sur le tas
 * @param instanceTableau un pointeur sur une structure de type InstanceTableau
 */
void InstanceTableau_videDetruire(InstanceTableau *instanceTableau){
    for(int i=0; i<instanceTableau->instancesNb; i++){
        free(instanceTableau->instances[i].Bi);
        free(instanceTableau->instances[i].Pj);
        free(instanceTableau->instances[i].Xj);
        for(int j=0; j<instanceTableau->instances[i].dimensionNb; j++)
            free(instanceTableau->instances[i].Rij[j]);
        free(instanceTableau->instances[i].Rij);
    }
    free(instanceTableau->instances);
    free(instanceTableau);
}

/** Rempli un tableau d'instances en parsant un fichier
 * @param instanceTableau un pointeur sur une structure de type InstanceTableau
 * @param instanceFichier un pointeur sur un fichier contenant des informations sur les instances
 * Préconditions : instanceTableau et instanceFichier non nuls
 */
void InstanceTableau_remplirInstances(InstanceTableau *instanceTableau, FILE *instanceFichier){
    if(instanceTableau == NULL || instanceFichier == NULL){
        printf("FATAL ERROR : FILE PARSE FAILED \n");
    }
    else{
        char *ligne = NULL;
        char *pEnd = ligne;

        ligne = lireLigne(instanceFichier);
        pEnd = ligne;
        instanceTableau->instancesNb = (int)strtol(pEnd,&pEnd,10);
        instanceTableau->instances = (Instance*)malloc(sizeof(Instance)*instanceTableau->instancesNb);
        free(ligne);

        //On saute une ligne du fichier
        ligne=lireLigne(instanceFichier);
        free(ligne);

        for(int i=0; i<instanceTableau->instancesNb; i++){
            time_t timer;
            timer = timer_start();
            Instance *instanceCourante = &instanceTableau->instances[i];

            //On saute les deux lignes qui séparent chaque instance
            for(int j=0; j<2; j++){
                ligne=lireLigne(instanceFichier);
                free(ligne);
            }


            //On lit les informations de l'instance
            ligne=lireLigne(instanceFichier); //Ligne qui contient le nombre d’objet N, le nombre de dimension M, les valeurs connues de solutions trouvée
            //Lecture des premiers paramètres de l'instance
            pEnd = ligne;
            for(int j=0; j<4; j++){
                switch (j){
                case 0:
                    instanceCourante->objetNb = (int)strtol(pEnd,&pEnd,10);
                    break;
                case 1:
                    instanceCourante->dimensionNb = (int)strtol(pEnd,&pEnd,10);
                    break;
                case 2:
                    instanceCourante->sol1 = (int)strtol(pEnd,&pEnd,10);
                    break;
                case 3:
                    instanceCourante->sol2 = (int)strtol(pEnd,&pEnd,10);
                    break;
                }
            }
            free(ligne);

            //Lecture des variables Xj
            ligne=lireLigne(instanceFichier);
            pEnd = ligne;
            instanceCourante->Xj = malloc(sizeof(int)*instanceCourante->objetNb);
            for(int j=0; j<instanceCourante->objetNb; j++){
                instanceCourante->Xj[j] = (int)strtol(pEnd,&pEnd,10);
            }
            free(ligne);

            //On saute une ligne
            ligne=lireLigne(instanceFichier);
            free(ligne);

            //Lecture des variables Pj
            ligne=lireLigne(instanceFichier);
            pEnd = ligne;
            instanceCourante->Pj = malloc(sizeof(int)*instanceCourante->objetNb);
            for(int j=0; j<instanceCourante->objetNb; j++){
                instanceCourante->Pj[j] = (int)strtol(pEnd,&pEnd,10);
            }
            free(ligne);

            //On saute une ligne
            ligne=lireLigne(instanceFichier);
            free(ligne);

            //Lecture des poids Rij pour chaque dimension
            instanceCourante->Rij = (int**)malloc(sizeof(int*)*instanceCourante->dimensionNb);
            for(int k=0; k<instanceCourante->dimensionNb; k++){
                ligne=lireLigne(instanceFichier);
                pEnd = ligne;
                instanceCourante->Rij[k] = (int*)malloc(sizeof(int)*instanceCourante->objetNb);
                for(int j=0; j<instanceCourante->objetNb; j++){
                    instanceCourante->Rij[k][j] = (int)strtol(pEnd,&pEnd,10);
                }
                free(ligne);
            }

            //On saute une ligne
            ligne=lireLigne(instanceFichier);
            free(ligne);

            //Lecture des variables Bi
            ligne=lireLigne(instanceFichier);
            pEnd = ligne;
            instanceCourante->Bi = (int*)malloc(sizeof(int)*instanceCourante->dimensionNb);
            for(int j=0; j<instanceCourante->dimensionNb; j++){
                instanceCourante->Bi[j] = (int)strtol(pEnd,&pEnd,10);
            }
            free(ligne);

            double time = timer_getTime(timer);
            printf("TIME : %lfs\n",time);
            timeFile(time,i+1);
        }
        printf("Fichier parsé avec succès\n");
    }
}

/** Lit la ligne suivante d'un fichier
 * @param fichier un pointeur sur un fichier texte
 * @return une chaine de caractère allouée sur le tas contenant la ligne du fichier
 */
char* lireLigne(FILE *fichier){
    char *p = NULL;
    char buf[2048];
    if(fgets(buf,sizeof(buf),fichier) != NULL)
        p = strdup(buf);
    return p;
}
