#include "PersonnageBase.h"

extern int NbColonnes;
extern int NbLignes;
extern char** matrice;

void PersonnageBase::BougerEnHaut() 
{
	if(PosL>0 && matrice[PosL-1][PosC]!='0')
	PosL--;
}
void PersonnageBase::BougerEnBas() 
{ 
	if(PosL<NbLignes-1 && matrice[PosL+1][PosC]!='0')
	PosL++;
}
void PersonnageBase::BougerAGauche() 
{ 
	if(PosC>0 && matrice[PosL][PosC-1]!='0')
	PosC--;
}
void PersonnageBase::BougerADroite() 
{ 
	if(PosC<NbColonnes-1 && matrice[PosL][PosC+1]!='0')
	PosC++;
}