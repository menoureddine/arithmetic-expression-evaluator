#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

/**
 *une structure pour faire la déférence entre les opérateur et opérandes
 */
 typedef struct
 {
 	double val;
 	int operand; /*booléen 1 => opérande */
 }Elm;

 /*les fonctions d'aide à l'étude syntaxique et lexique de l'expression*/

 /*langueur max de l'expression*/
 #define L_MAX 100

 /**
  *charAdmis(char c)
  *vérification si c'est un caractère valide
  */
int charAdmis(char c);

/**
 *lexiqueJuste(char* exp)
 *analyse lexical de l'expression exp
 */
int lexiqueJuste(char* exp);

/**
 *charOperande(char c)
 *return 1 si le caractère c est un opérande
 */
int charOperande(char c);

/**
 *charOperateur(char c)
 *return 1 si le caractère c est un opérateur
 */
int charOperateur(char c);


/**
 *syntaxiqueJuste(char* exp)
 *analyse syntaxique de l'expression exp
 */
int syntaxiqueJuste(char* exp);


/**
 *chaineAuFloat(char *ch, Elm *t)
 *Transformer la chaîne de caractère en vecteur de Elm
 **/
void chaineAuFloat(char *ch, Elm *t, int *n);


/**
 *operateur(Elm e)
 *déterminer si e est un opérateur
 */
int operateur(Elm e);


/**
 *operande(Elm e)
 *déterminer si e est un opérande
 */
int operande(Elm e);


/**
 *priorite(Elm e)
 *return la priorité de l'opérateur
 * 1 => { *, /, % }
 * 2 => { +, - }
 */
int priorite(Elm e);

/**
 *operation(Elm x1, Elm op, Elm x2)
 *effectuer l'opération x1 op x2
 */
double operation(Elm x1, Elm op, Elm x2);

/**
 *afficheElm(Elm e)
 *fonction d'aide pour l'affichage des elements
 */
void afficheElm(Elm e);

#endif // EXPRESSION_H_INCLUDED
