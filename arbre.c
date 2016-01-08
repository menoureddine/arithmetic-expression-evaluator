#include "arbre.h"

int arbreVide(Arbre* a)
{
	if (a == NULL)
		return 1;
	else
		return 0;
}

Arbre* succGauche(Arbre* a)
{
	return a->succ_g;
}

Arbre* succDroit(Arbre* a)
{
	return a->succ_d;
}

int feuil(Arbre* a)
{
	if (( succDroit(a) == NULL )&&( succGauche(a) == NULL ))
		return 1;
	else
		return 0;
}

Arbre* creatFeuil(Elm e)
{
	Arbre* a;
	a = (Arbre*)malloc(sizeof(Arbre));
	a->info = e;
	a->succ_g = NULL;
	a->succ_d = NULL;
	return a;
}


void initPileA(PileAebre** p)
{
	(*p) = NULL;
}

int pileAVide(PileAebre* p)
{
	return p == NULL;
}

Arbre* sommetPileA(PileAebre* p)
{
	return p->info;
}

void empilerA(PileAebre** p, Arbre* a)
{
	PileAebre* q;
	q = (PileAebre*)malloc(sizeof(PileAebre));
	q->info = a;
	q->svt = (*p);
	(*p) = q;
}

void depilerA(PileAebre** p, Arbre** a)
{
	PileAebre* q;
	q = (*p);
	(*p) = q->svt;
	(*a) = q->info;
	free(q);
}

Arbre* constArbre(Elm* t, int n)
{
	/*Transformation de forme infixée au forme postfixée*/
	Pile *p;
	initPile(&p);
	p = infexeeAuPostfixee(t, n);
	/*création de l'arbre*/
	Arbre* f;
	Arbre* f1;
	Arbre* f2;
	/*initialiser la pile des Arbres*/
	PileAebre* pArbre;
	initPileA(&pArbre);

	Elm x;
	while(!pileVide(p))
	{
		depiler(&p, &x);
		if(operande(x))
		{
			f = creatFeuil(x);
			empilerA(&pArbre, f);
		}
		else
		{
			/*construire une sous arbre*/
			f = creatFeuil(x);
			depilerA(&pArbre, &f1);
			depilerA(&pArbre, &f2);
			f->succ_d = f1;
			f->succ_g = f2;
			empilerA(&pArbre, f);
		}
	}
	/*la racine de l'arbre se trouve a la pile des arbres et la pile p est vide*/
	return sommetPileA(pArbre);
}


double evaluerArbre(Arbre* a)
{
	Elm x, y;
	if(!arbreVide(a))
	{
		if(operateur(a->info))
		{
			x.val = evaluerArbre(succGauche(a));
			y.val = evaluerArbre(succDroit(a));
			return operation(x, a->info, y);
		}
		else
			return a->info.val;
	}
}


void afficheArbre(Arbre* a)
{
	if(!arbreVide(a))
	{
        printf("noeud actuelle: ");
        afficheElm(a->info);
        printf(".....fils gauche: ");
        if(succGauche(a))
			afficheElm(succGauche(a)->info);
		else
			printf("[NULL]");
        printf(".....fils droit: ");
        if(succDroit(a))
			afficheElm(succDroit(a)->info);
		else
			printf("[NULL]");
        printf("\n");
        afficheArbre(succGauche(a));
        afficheArbre(succDroit(a));
	}
}
