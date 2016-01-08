#include "expression.h"

int charAdmis(char c)
{
	if ( ((c >= '0')&&(c <= '9')) ||
		 (c == '+') || (c == '-') ||
		 (c == '*') || (c == '/') || (c == '%') ||
		 (c == '(') || (c == ')') ||
		 (c == 'e') || (c == 'E') || (c == '.'))
			return 1;
	else
		return 0;
}

int lexiqueJuste(char* exp)
{
	int i;
	/*vérifier si tout les caractères sont admis*/
	for(i = 0; (i < L_MAX)&&(exp[i] != '\0'); i++)
		if ( !charAdmis(exp[i]) )
			return 0;
	return 1;
}

int charOperande(char c)
{
	if ((c >= '0')&&(c <= '9'))
		return 1;
	else
		return 0;
}

int charOperateur(char c)
{
	if ((c == '+') || (c == '-') ||
		(c == '*') || (c == '/') || (c == '%'))
		return 1;
	else
		return 0;
}

int syntaxiqueJuste(char* exp)
{
	int i;
	int nbParO = 0, nbParF = 0; //nombre de parenthèses ouvrantes et fermentes
	//début de l'expression doit être un opérande ou signe - ou '(' sinon je retourne 0
	if (!charOperande(exp[0])&&(exp[0] != '-')&&(exp[0]!='('))
		return 0;
	//return 0 si 2 signes '-' au début
	if ((exp[0] == '-')&&(exp[1] == '-'))
		return 0;
	//incrémenter nbParO si on commence par '('
	if (exp[0] == '(')
		nbParO++;
	//vérifier le reste
	for(i = 1; (i < L_MAX-1) && (exp[i] != '\0'); i++)
	{
		/*return 0 si exp[i] un opérateur et ch[i+1] est ni opérande ni signe '-' ni '('
			on ne peut pas avoir deux opérateurs successive */
		if((charOperateur(exp[i]))&&(!charOperande(exp[i+1]))&&(exp[i+1] != '(')&&(exp[i+1] != '-'))
			return 0;
		/*return 0 si exp[i] est '(' et ch[i+1] est ni opérande ni signe '-' ni '('
			on ne peut pas avoir deux opérateurs successive */
		if((exp[i] == '(')&&(!charOperande(exp[i+1]))&&(exp[i+1] != '(')&&(exp[i+1] != '-'))
			return 0;
		/*return 0 si exp[i] est une ')' et exp[i+1] n'est pas un opérateur
		   on ne peut pas avoir une '(' suivie par une opérande */
		if ((exp[i] == ')')&&(exp[i+1] != ')')&&(exp[i+1] != '\0')&&(!charOperateur(exp[i+1])))
			return 0;
		/*return 0 si exp[i] est un opérande et exp[i+1] est '('
			un opérande ne peut pas être suivi par '('*/
		if((charOperande(exp[i]))&&(exp[i+1] == '('))
			return 0;
		/*return 0 si plus de 3 signe '-' successive
		   on accepte le cas de a--y <=> a - (-y) */
		if((exp[i-1] == '-')&&(exp[i] == '-')&&(exp[i+1] == '-'))
			return 0;
		/*return 0 si . après pas un chiffre (opérande) */
		if((exp[i] == '.')&&(!charOperande(exp[i+1])))
			return 0;
		/*calcule de nombre de '(' et ')' */
		if (exp[i] == '(')
			nbParO++;
		else if (exp[i] == ')')
			nbParF++;
	}
	//À la sortie de la boucle
	/*vérifier le nombre de parenthèse ouvrante et fermente*/
	if (nbParO != nbParF)
		return 0;
	/*il n'y a aucune erreur */
	return 1;
}

void chaineAuFloat(char *ch, Elm *t, int *n)
{
	 int iCh, iT, iC;
    char c[L_MAX];
    for(iCh = 0, iT =0; (iCh < L_MAX)&&(ch[iCh] != '\0'); iT++)
	{
		if(ch[iCh] == '(')
		{ /*insertion du Elm de la '(' 6 : 0 */
			t[iT].val = 6.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == ')')
		{/*insertion du Elm de la ')' 7 : 0 */
			t[iT].val = 7.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '*')
		{/*insertion du Elm de la '*' 1 : 0 */
			t[iT].val = 1.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '/')
		{/*insertion du Elm de la '/' 2 : 0 */
			t[iT].val = 2.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '%')
		{/*insertion du Elm de la '%' 3 : 0 */
			t[iT].val = 3.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '+')
		{/*insertion du Elm de la '+' 4 : 0 */
			t[iT].val = 4.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if ((ch[iCh] == '-')&&(iCh > 0)&&(!charOperateur(ch[iCh-1]))&&(ch[iCh-1] != '('))
		{/*insertion du Elm de la '-' 5 : 0 */
			t[iT].val = 5.0;
			t[iT].operand = 0;
			iCh++;
		}
		else
		{ /*nous avons un opérande */
			//récupérer tout l'opérande dans la chaîne c
			for(iC = 0; (ch[iCh] != '\0'); iC++, iCh++)
			{
				/*on arrête a la rencontre d'un opérande suivi par un opérateur ou une ')'*/
				if((charOperande(ch[iCh - 1]))&&((charOperateur(ch[iCh]))||(ch[iCh] == ')')))
					break;
				c[iC] = ch[iCh];
			}
			/*finir la chaîne c par '\0' */
			c[iC] = '\0';
			/*transformer la chaîne c on float et la stocker dans le tableau */
			t[iT].val = atof(c);
			t[iT].operand = 1;
		}
	}
	/*récupérer le nombre d'élément dans n*/
	*n = iT;
}


int operateur(Elm e)
{
	/*opérateur déférant de opérande et déférant de '(' et de ')'*/
	if( (!e.operand)&&(e.val != 6.0)&&(e.val != 7.0))
		return 1;
	else
		return 0;
}

int operande(Elm e)
{
	return e.operand;
}

int priorite(Elm e)
{
	/*
	 * 1=> '*'
	 * 2=> '/'
	 * 3=> '%'
	 */
	if ((e.val == 1.0)||(e.val == 2.0)||(e.val == 3.0))
		return 1;
	else
		return 2;
}

double operation(Elm x1, Elm op, Elm x2)
{
	if(op.val == 1.0)
		return x1.val * x2.val;
	else if(op.val == 2.0)
		return x1.val / x2.val;
	else if(op.val == 3.0)
		return (double)((int)(x1.val) % (int)(x2.val));
	else if(op.val == 4.0)
		return x1.val + x2.val;
	else //op.val == 5.0
		return x1.val - x2.val;

}


void afficheElm(Elm e)
{
	if(operande(e))
	{//si e est un operande on affiche 3 chifre apres la virgule
		printf("[%.3f]", e.val);
	}
	else
	{//si c'est deferant de l'operande en affiche son code entaire
		printf("[%3.0f]", e.val);
	}
}
