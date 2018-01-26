#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"

#define CODAGEDIRECT 1
#define CODAGEINDIRECT 2
#define HEURISTIQUE 1
#define METAHEURISTIQUE 2

/** Structure qui stocke les paramètres lors de l'appel du programme
 */
typedef struct _Parametres{
    char* cheminFichier;
    int codage;
    int methode;
    int paramMethode;
} Parametres;

/** Structure qui stocke les données d'une instance d'un problème
 */
typedef struct _Instance{
    int objetNb;
    int dimensionNb;
    int sol1;
    int sol2;
    int *Xj; //Les variables Xj des solutions trouvées
    int *Pj; //La valeur des objets
    int *Bi; //Poids à ne pas dépasser pour chaque dimension
    int **Rij; //Pour chaque dimension la valeur des poids
} Instance;

/** Structure qui stocke un tableau d'instances
 */
typedef struct _InstanceTableau{
    Instance *instances;
    int instancesNb;
} InstanceTableau;

/** Retourne un tableau d'instances initialisé créé sur le tas
 * @return un pointeur sur un tableau d'instances
 */
InstanceTableau * InstanceTableau_initCreer();

/** Vide et détruit un tableau d'instances créé sur le tas
 * @param InstanceTableau un pointeur sur une structure de type InstanceTableau
 */
void InstanceTableau_videDetruire(InstanceTableau *instanceTableau);

/** Rempli un tableau d'instances en parsant un fichier
 * @param InstanceTableau un pointeur sur une structure de type InstanceTableau
 * @param instanceFile un pointeur sur un fichier contenant des informations sur les instances
 * Préconditions : InstanceTableau et instanceFile non nuls
 */
void InstanceTableau_remplirInstances(InstanceTableau *instanceTableau, FILE *instanceFichier);

/** Lit la ligne suivante d'un fichier
 * @param file un pointeur sur un fichier texte
 * @return une chaine de caractère allouée sur le tas contenant la ligne du fichier
 */
char* lireLigne(FILE *fichier);

#endif // INSTANCE_H_INCLUDED
