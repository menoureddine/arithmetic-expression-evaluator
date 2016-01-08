#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "pile.h"


/** Primitives des Arbres binaire **/

/**
 *Définition de la structure
 */
typedef struct elmArbre
{
	Elm info;
	struct elmArbre* succ_g;
	struct elmArbre* succ_d;
}Arbre;

/**
 *arbreVide(Arbre*)
 *Vérifier si l'arbre est vide
 *return 0 <=> arbre non vide
 */
int arbreVide(Arbre* a);

/**
 *succGauche(Arbre*)
 *return adresse du successeur gauche
 */
Arbre* succGauche(Arbre* a);

/**
 *succDroit(Arbre*)
 *return adresse du successeur droit
 */
Arbre* succDroit(Arbre* a);

/**
 *feuil(Arbre*)
 *vérifier si le noeud est une feuil
 *return 0 <=> pas une feuil
 */
int feuil(Arbre* a);

/**
 *creatFeuil(Elm e)
 *return une feuil avec e
 */
Arbre* creatFeuil(Elm e);

/*Fonctions de transformation de l'expression arithmétique à une arbre binaire
	en utilisant la forme postfixée et une pile des arbres*/
/**
 *définition de la structure de la pile des arbres
 */
typedef struct elmPileArbre
{
	Arbre* info;
	struct elmPileArbre* svt;
}PileAebre;

void initPileA(PileAebre** p);

int pileAVide(PileAebre* p);

Arbre* sommetPileA(PileAebre* p);

void empilerA(PileAebre** p, Arbre* a);

void depilerA(PileAebre** p, Arbre** a);


/**
 *constArbre(Pile* p)
 *return la racine de l'arbre contenant l'expression arithmétique
 */
Arbre* constArbre(Elm* t, int n);


/**
 *evaluerArbre(Arbre* a)
 *return le résultat de l'évaluation de l'expression à partir de l'arbre
 */
double evaluerArbre(Arbre* a);

/**
 *afficheArbre(Arbre* a)
 *afficher les noeuds de l'arbre un par un avec ses fils
 */
void afficheArbre(Arbre* a);

#endif // ARBRE_H_INCLUDED
