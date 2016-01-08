#include "pile.h"

void initPile(Pile **p)
{
	(*p) = NULL;
}

int pileVide(Pile* p)
{
	if ( p == NULL)
		return 1;
	else
		return 0;
}

Elm sommetPile(Pile* p)
{
	if (!pileVide(p))
		return p->info;
	else
		printf("erreur: Pile vide");
}

void empiler(Pile** p, Elm e)
{
	Pile* q;
	q = (Pile*)malloc(sizeof(Pile));
	q->info = e;
	q->svt = (*p);
	(*p) = q;
}

void depiler(Pile** p, Elm* e)
{
	Pile *sommet;
	sommet = (*p);
	(*p) = sommet->svt;
	*e = sommet->info;
	free(sommet);
}

Pile* infexeeAuPostfixee(Elm* t, int n)
{
	Pile *p, *r;
	Elm x;
	int i;
	initPile(&p);
	initPile(&r);
	for(i = 0; i < n; i++)
	{
		if(operande(t[i]))
			empiler(&r, t[i]);
		else if(operateur(t[i]))
		{
			while((!pileVide(p))&&(operateur(sommetPile(p)))&&(priorite(t[i]) >= priorite(sommetPile(p))))
			{
				depiler(&p, &x);
				empiler(&r, x);
			}
			empiler(&p, t[i]);
		}
		else if(t[i].val == 6.0)
			empiler(&p, t[i]);
		else
		{
			while((!pileVide(p)) && !((sommetPile(p).val == 6.0)&&(!sommetPile(p).operand)))
			{
				depiler(&p, &x);
				empiler(&r, x);
			}
			depiler(&p, &x);
		}
	}
	while(!pileVide(r))
	{
		depiler(&r, &x);
		empiler(&p, x);
	}
	return p;
}


void affichePiles(Pile* p, Pile* r)
{
	printf("\t[  p  ]\t\t[  r  ]\n");
	/*on va traiter les piles comme des liste chaines simples pour ne pas perdre les élément*/
	Pile* pTmp;
	Pile* rTmp;
	for( pTmp = p, rTmp = r; (pTmp)&&(rTmp); pTmp = pTmp->svt, rTmp = rTmp->svt)
	{
		printf("\t");
		afficheElm(pTmp->info);
		printf("\t\t");
		afficheElm(rTmp->info);
		printf("\n");
	}
	for( ;(pTmp); pTmp = pTmp->svt)
	{
		printf("\t");
		afficheElm(pTmp->info);
		printf("\n");
	}
	for( ;(rTmp); rTmp = rTmp->svt)
	{
		printf("\t\t\t");
		afficheElm(rTmp->info);
		printf("\n");
	}
}



double evaluer(Pile** p)
{
	Elm resultat, x, x1, x2;
	resultat.operand = 1;
	Pile *r;
	initPile(&r);
	while(!pileVide((*p)))
	{
		affichePiles( *p, r);
		depiler(p, &x);
		if (operande(x))
			empiler(&r, x);
		else
		{
			depiler(&r, &x2);
			depiler(&r, &x1);
			resultat.val = operation(x1, x, x2);
			empiler(&r, resultat);
		}
		//printf("----------------------------------\n");
	}
	return sommetPile(r).val;
}
