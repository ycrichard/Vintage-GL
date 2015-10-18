#include "Joueur.h"

extern int NbColonnes;
extern int NbLignes;
extern char** matrice;

void Joueur::Dessiner()
{
	glPushMatrix();
	glTranslated(PosC+0.5,PosL+0.5,0.0);
		glColor3d(0.0,0.0,0.0);				//noire
		glutSolidSphere(0.3,12,12);

		glColor3d(1.0,1.0,0.0);			//jaunne
		glTranslated(0.1,-0.1,0.0);
			glutSolidSphere(0.05,12,12);
		glColor3d(1.0,1.0,0.0);
		glTranslated(-0.2,0.0,0.0);
			glutSolidSphere(0.05,12,12);
	glPopMatrix();
}
