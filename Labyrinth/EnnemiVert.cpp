#include "EnnemiVert.h"

extern int NbColonnes;
extern int NbLignes;
extern char** matrice;

void EnnemiVert::Dessiner()
{
	glPushMatrix();
	glTranslated(PosC+0.5, PosL+0.5, 0.0);
		glColor3d(0.0, 0.9, 0.0);			//vert
		glutSolidSphere(0.3, 12 , 12);

		glPushMatrix();
			glTranslated(0.0 , -0.13, 0.0);
			glScaled(1.0 ,0.5 ,1.0);
			glutSolidCube(0.5);				//les cornes
		glPopMatrix();

		glColor3d(1.0, 0.0 ,0.0);
		glTranslated(-0.3, -0.1, 0.0);
		for(int i=0;i<3;i++)
		{
			glTranslated(0.15, 0.0, 0.0);
			glutSolidSphere(0.05, 12, 12);
		}
	glPopMatrix();
}