#ifndef METAHEURISTIQUE_H_INCLUDED
#define METAHEURISTIQUE_H_INCLUDED

#include "instance.h"
#include "codage.h"

/** Metaheuristique locale indirecte
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaLocalIndirecte(int* tab, Instance *instance);

/** Metaheuristique locale directe
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaLocalDirecte(int* tab, Instance *instance);

/** Metaheuristique tabou indirecte
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param TabouSize le nombre de solutions taboues
 * @param aspi le critère d'aspiration (1 si on active le critère d'aspiration, 0 sinon)
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaTabouIndirecte(int* tab, Instance *instance, int nbIteMax, int tabouSize, int aspi);

/** Metaheuristique tabou directe
 * @param tab le tableau dans lequel sera stocké la solution
 * @param instance l'instance à utiliser pour générer la solution
 * @param NbIteMax le nombre d'itérations maximum sans trouver une meilleure solution courante
 * @param aspi le critère d'aspiration (1 si on active le critère d'aspiration, 0 sinon)
 * @param tailleListe la taille de la liste de mouvement taboues
 * Préconditions : tab non nul, et d'une taille correspondant au nombre d'objets de l'instance
 */
void metaTabouDirecte(int* tab, Instance *instance, int nbIteMax, int aspi, int tailleListe);

#endif // METAHEURISTIQUE_H_INCLUDED
