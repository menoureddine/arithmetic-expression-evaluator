#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
#include "pile.h"
#include "arbre.h"

int choisireTypeEvaluation()
{
	int chois;
	do
	{
		puts("Choisissez un type d'evaluation:");
		puts("1: Evaluation en utilisant les piles.");
		puts("2: Evaluation en utilisant les arbres.");
		printf("> ");
		scanf("%d", &chois);
	}while((chois != 1)&&(chois != 2));
	return chois;
}

int main()
{
	char Exp[L_MAX];
	int syn, lex;
	int ChoisTypeEvaluation;
	Elm t[L_MAX];
	int n;
	Pile* p;
	float resultat;
	Arbre* a;
	char repeter;
	do
	{
		/*récupérer l'expression à évaluer*/
		printf("donner votre expression sans espaces:\n>");
		scanf("%s", Exp);
		/*vérification lexical et syntaxique de l'expression*/
		syn = lex = 0;
		lex = lexiqueJuste(Exp);
		syn = lex? syntaxiqueJuste(Exp) : 0;
		if(!lex)
			printf("Expression non correct lexicalement.\n");
		else if(!syn)
			printf( "Expression non correct syntaxiquement.\n");
		else
		{
			/*récupérer le type d'évaluation on utilisant les arbres ou les piles*/
			ChoisTypeEvaluation = choisireTypeEvaluation();

			/*transformation de l'expression a un tableau de 'Elm's*/
			chaineAuFloat(Exp, t, &n);

			/*procéder l'évaluation le chois de l'utilisateur*/
			switch (ChoisTypeEvaluation)
			{
				case 1:
					initPile(&p);
					/*création de la pile*/
					p = infexeeAuPostfixee(t, n);
					resultat = evaluer(&p);
					printf("Resultat de l'evaluation est: %.3f\n", resultat);
					break;
				case 2:
					a = constArbre(t, n);
					//affichage de l'arbre
					afficheArbre(a);
					resultat = evaluerArbre(a);
					printf("Resultat de l'evaluation est: %.3f\n", resultat);
			}
		}
		puts("Voulez vous evaluer une autre expression?(o/n)");
		printf("> ");
		//vider le buffer
		while ((repeter = getchar()) != '\n' && repeter != EOF);
		scanf( "%c", &repeter);
	}while((repeter == 'o')||(repeter == 'O'));

    return 0;
}
