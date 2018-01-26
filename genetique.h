#ifndef GENETIQUE_H_INCLUDED
#define GENETIQUE_H_INCLUDED

#include "heuristique.h"
#include "codage.h"

#define DIRECT 0
#define INDIRECT 1


typedef struct _Population{
    int **solutions;
    int taillePopu;
    int type;
} Population;

/** Initialise une population vide de type direct ou indirect
 * @param population un pointeur de type Population, non initialisé
 * @param taillePopulation la taille de la population
 * @param typeSolutions type direct ou indirect
 */
void initPopulation(Population *population, int taillePopulation, int typeSolutions);

/** Initialise et génère une population de type direct ou indirect
 * @param population un pointeur de type Population, non initialisé
 * @param taillePopulation la taille de la population
 * @param typeSolutions type direct ou indirect
 * @param instance l'instance à utiliser pour générer la population
 */
void creerPopulation(Population *population, int taillePopulation, int typeSolutions, Instance *instance);

/** Détruit une population
 * @param population la population à détruire
 */
void detruirePopulation(Population *population);


/**
|||||||||||||||||||||||||||||||||||||||||||||||

               PARTIE DIRECTE

|||||||||||||||||||||||||||||||||||||||||||||||
**/


/** Metaheuristique génétique direct
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param taillePopu la taille de la population à utiliser
 * @param pMut la probabilité de mutation d'un enfant
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaGenetiqueDirecte(int* tab, Instance *instance, int nbIteMax, int taillePopu, int pMut);

/** Génère deux enfants au format direct à partir de deux parents donnés
 * @param parent1, parent2 les parents à utiliser
 * @param enfant1, enfant2 pointeurs dans lesquels seront stockés les 2 enfants
 * @param instance l'instance associée aux deux parents
 * Préconditions : parent1, parent2, enfant1 et enfant2 correctement initialisés
 */
void procreerDirect(int *parent1, int *parent2, int *enfant1, int *enfant2, Instance *instance);

/** Mute un membre de la population au format direct
 * @param membre le membre à muter
 * @param instance l'instance associée au membre
 * Préconditions : membre correctement initialisé
 */
void mutationDirect(int *membre, Instance *instance);

/** Renouvelle une population à partir d'une nouvelle population de façon à ne garder que les meilleurs membres des 2 populations
 * @param aEvoluer la population à renouveller
 * @param nouvelle la population à utiliser pour le renouvellement
 * @param instance l'instance associée aux populations
 * Préconditions : populations initialisées et non vides
 */
void renouvellerDirect(Population *aEvoluer, Population *nouvelle, Instance *instance);


/**
|||||||||||||||||||||||||||||||||||||||||||||||

               PARTIE INDIRECTE

|||||||||||||||||||||||||||||||||||||||||||||||
**/


/** Metaheuristique génétique indirect
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param taillePopu la taille de la population à utiliser
 * @param pMut la probabilité de mutation d'un enfant
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaGenetiqueIndirecte(int* tab, Instance *instance, int nbIteMax, int taillePopu, int pMut);

/** Génère deux enfants au format indirect à partir de deux parents donnés
 * @param parent1, parent2 les parents à utiliser
 * @param enfant1, enfant2 pointeurs dans lesquels seront stockés les 2 enfants
 * @param instance l'instance associée aux deux parents
 * Préconditions : parent1, parent2, enfant1 et enfant2 correctement initialisés
 */
void procreerIndirect(int *parent1, int *parent2, int *enfant1, int *enfant2, Instance *instance);

/** Algorithme PMX pour créer un enfant en solution indirecte à partir de 2 parents
 * @param parent1, parent2 les parents à utiliser
 * @param enfant pointeur sur la solution enfant
 * @param pointCroisement1, pointCroisement2 les points de croisements à utiliser
 * @param instance l'instance associée aux deux parents
 * Préconditions : parent1, parent2, enfant1 et enfant2 correctement initialisés
**/
void PMX(int *parent1, int *parent2, int *enfant, int pointCroisement1, int pointCroisement2, Instance *instance);

/** Mute un membre de la population au format indirect
 * @param membre le membre à muter
 * @param instance l'instance associée au membre
 * Préconditions : membre correctement initialisé
 */
void mutationIndirect(int *membre, Instance *instance);

/** Renouvelle une population à partir d'une nouvelle population de façon à ne garder que les meilleurs membres des 2 populations
 * @param aEvoluer la population à renouveller
 * @param nouvelle la population à utiliser pour le renouvellement
 * @param instance l'instance associée aux populations
 * Préconditions : populations initialisées et non vides
 */
void renouvellerIndirect(Population *aEvoluer, Population *nouvelle, Instance *instance);

#endif // GENETIQUE_H_INCLUDED
