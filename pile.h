#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "expression.h"

/**
 *la structure de la pile
 */
typedef struct elmPile
{
	Elm info;
	struct elmPile* svt;
}Pile;

/*primitives des piles*/
/**
 *initPile(Pile** p)
 *initialiser la pile à NULL
 */
void initPile(Pile** p);


/**
 *pileVide(Pile* p)
 *vérifier si la pile est vide
 */
int pileVide(Pile* p);


/**
 *sommetPile(Pile* p)
 *returner la valeur que se trouve au sommer de la pile
 */
Elm sommetPile(Pile* p);


/**
 *empiler(Pile** p, Elm e)
 *empiler e dans la pile p
 */
void empiler(Pile** p, Elm e);


/**
 *depiler(Pile** p, Elm* e)
 *dépiler un élément de la pile p dans e
 */
void depiler(Pile** p, Elm* e);

/**
 *infexeeAuPostfixee(Elm* t, int n)
 *return pile des éléments du tableau t sous forme postfixée
 */
Pile* infexeeAuPostfixee(Elm* t, int n);


/**
 *affichePiles(Pile* p, Pile* r)
 *fonction d'aide pour afficher l'etat des piles après chaque traitement
 */
void affichePiles(Pile* p, Pile* r);



/**
 *evaluer(Pile* p)
 *évaluer la forme postfixée de la pile
 */
double evaluer(Pile** p);




#endif // PILE_H_INCLUDED
