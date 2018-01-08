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

#endif // METAHEURISTIQUE_H_INCLUDED
