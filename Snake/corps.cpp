#include "corps.h"

extern int NbColonnes;
extern int NbLignes;
extern char** matrice;
extern void LibererMemoire();
extern void EndOut();

void corps::Bouger()
{
	switch(Dir)
	{
	case haut:{
		PosL--;
		if(PosL<0) PosL=NbLignes-1;
		break;}
	case bas:{
		PosL++;
		if(PosL>=NbLignes) PosL=0;
		break;}
	case gauche:{
		PosC--;
		if(PosC<0) PosC=NbColonnes-1;
		break;}
	case droite:{
		PosC++;
		if(PosC>=NbColonnes) PosC=0;
		break;}
	}
}

void corps::TestCollision()
{
	if(matrice[PosL][PosC]== '0')
	{
		EndOut();
		LibererMemoire();
		#ifdef _WIN32
            system("pause");
        #else
            cout<<"Press enter to continue > "<<endl;
            getchar();
        #endif
		exit(0);
	}
}

void corps::SeCollision(corps* c)
{
	if(PosL==c->PosL && PosC==c->PosC)
	{
		EndOut();
		LibererMemoire();
		#ifdef _WIN32
            system("pause");
        #else
            cout<<"Press enter to continue > "<<endl;
            getchar();
        #endif
		exit(0);
	}
}
void corps::Dessiner()
{
	glPushMatrix();
	glTranslated(PosC+0.5, PosL+0.5, 0.0);
		glColor3d(0.9, 0.0, 0.0);			//rouge
		glutSolidCube(0.8);
		glColor3d(0.8, 0.7, 0.0);
		glutWireCube(0.8);
	glPopMatrix();
}

void corps::Suivre(corps* c)
{
	PosC=c->GetPosC();
	PosL=c->GetPosL();
	Dir=c->GetDir();
}
