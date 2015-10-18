#include "box.h"

void box::Dessiner()
{
	if(!appear) return;
	glPushMatrix();
	switch(couleur)
	{
	case rouge:glColor3d(0.9, 0.0, 0.0);break;
	case vert:glColor3d(0.0, 0.8, 0.0);break;
	case bleu:glColor3d(0.0, 0.0, 1.0);break;
	case jaune:glColor3d(0.94, 0.94, 0.0);break;
	case rose:glColor3d(0.8, 0.0, 1.0);break;
	case orange:glColor3d(1.0, 0.5, 0.0);break;
	case aqua:glColor3d(0.0, 0.88, 0.88);break;
	case gris:glColor3d(0.34, 0.34, 0.34);break;
	}
	
	glTranslated(X+0.5, Y+0.5, 0.0);			
		glutSolidCube(1.0);				
	glColor3d(1.0, 1.0, 1.0);			
		glutWireCube(1.0);				
	glPopMatrix();
}