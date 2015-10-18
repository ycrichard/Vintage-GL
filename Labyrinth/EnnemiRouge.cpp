#include "EnnemiRouge.h"

extern int NbColonnes;
extern int NbLignes;
extern char** matrice;
enum TYPE_ENNEMI { vert,rouge };
extern void AddEnnemi(TYPE_ENNEMI type,int PosC, int PosL);

void EnnemiRouge::Dessiner()
{
	glPushMatrix();
	glTranslated(PosC+0.5, PosL+0.5, 0.0);
		glColor3d(0.9, 0.0, 0.0);			//rouge

		glPushMatrix();
			glScaled(0.7 ,1.0 ,1.0);
			glutSolidSphere(0.35, 12, 12);				// ovale
		glPopMatrix();

		glPushMatrix();
			glScaled(1.0 ,0.7 ,1.0);
			glutSolidSphere(0.35, 12, 12);				// ovale
		glPopMatrix();

		glColor3d(0.0, 0.0 ,0.0);
		glTranslated(0.13, -0.05, 0.0);
			glutSolidSphere(0.07, 12, 12);
		glTranslated(-0.26, 0.0, 0.0);
			glutSolidSphere(0.07, 12, 12);
	glPopMatrix();
}

void EnnemiRouge::DeplacementAuto()
{
	if( rand()%50==0 )
		AddEnnemi(rouge,PosC,PosL);

	EnnemiBase::DeplacementAuto();
}
