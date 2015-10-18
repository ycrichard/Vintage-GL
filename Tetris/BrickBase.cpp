#include "BrickBase.h"

BrickBase::BrickBase()
{
	CentreX=7; 
	CentreY=-1; 
	//X1=X2=X3=Y1=Y2=Y3=0; 
	//couleur=gris;
	/*switch(rand()%8)
	{
	case 0:couleur=rouge;break;
	case 1:couleur=vert;break;
	case 2:couleur=bleu;break;
	case 3:couleur=jaune;break;
	case 4:couleur=rose;break;
	case 5:couleur=orange;break;
	case 6:couleur=aqua;break;
	case 7:couleur=gris;break;
	}*/
}
BrickBase::~BrickBase()
{
  // destructor test
  // cout << "Brick " << this << " is destroyed" << endl;
}

void BrickBase::Tomber()
{
	//if(CentreY<21 && Y1<21 && Y2<21 && Y3<21)
	//{
		CentreY++;
		Y1++;
		Y2++;
		Y3++;
	//}
}

void BrickBase::Dessiner()
{
	switch(couleur)
	{
	case rouge:glColor3d(0.9, 0.0, 0.0);break;
	case vert:glColor3d(0.0, 0.8, 0.0);break;
	case bleu:glColor3d(0.0, 0.0, 1.0);break;
	case jaune:glColor3d(0.94, 0.94, 0.0);break;
	case rose:glColor3d(0.8, 0.0, 1.0);break;
	case orange:glColor3d(1.0, 0.5, 0.0);break;
	case aqua:glColor3d(0.0, 0.88, 0.88);break;
	case gris:glColor3d(0.5, 0.5, 0.5);break;
	}
	glPushMatrix();
	glTranslated(CentreX+0.5, CentreY+0.5, 0.0);			
		glutSolidCube(1.0);				
	glPopMatrix();

	glPushMatrix();
	glTranslated(X1+0.5, Y1+0.5, 0.0);			
		glutSolidCube(1.0);			
	glPopMatrix();

	glPushMatrix();
	glTranslated(X2+0.5, Y2+0.5, 0.0);			
		glutSolidCube(1.0);				
	glPopMatrix();

	glPushMatrix();
	glTranslated(X3+0.5, Y3+0.5, 0.0);			
		glutSolidCube(1.0);				
	glPopMatrix();

	glColor3d(1.0, 1.0, 1.0); 
	glPushMatrix();
	glTranslated(CentreX+0.5, CentreY+0.5, 0.0);			
		glutWireCube(1.0);				
	glPopMatrix();

	glPushMatrix();
	glTranslated(X1+0.5, Y1+0.5, 0.0);			
		glutWireCube(1.0);			
	glPopMatrix();

	glPushMatrix();
	glTranslated(X2+0.5, Y2+0.5, 0.0);			
		glutWireCube(1.0);				
	glPopMatrix();

	glPushMatrix();
	glTranslated(X3+0.5, Y3+0.5, 0.0);			
		glutWireCube(1.0);				
	glPopMatrix();
}

void BrickBase::Translate(int a,int b)
{
	X1+=a;X2+=a;X3+=a;CentreX+=a;
	Y1+=b;Y2+=b;Y3+=b;CentreY+=b;
}

void BrickBase::BougerAGauche()
{
	//if(X1>0 && X2>0 && X3>0 && CentreX>0)
	{X1--;X2--;X3--;CentreX--;}
}

void BrickBase::BougerADroite()
{
	//if(X1<14 && X2<14 && X3<14 && CentreX<14)
	{X1++;X2++;X3++;CentreX++;}
}