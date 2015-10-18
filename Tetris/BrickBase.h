#ifndef BrickBase_h
#define BrickBase_h

#include <iostream>
using namespace std;
#include "GL/glut.h"
#include "color.h"

class BrickBase
{
protected:
	int CentreX;
	int CentreY;
	int X1,X2,X3,Y1,Y2,Y3;
	COLOR couleur;
public:
	BrickBase();
	~BrickBase();
	COLOR GetCouleur() {return couleur;}
	int GetX1() {return X1;}
	int GetX2() {return X2;}
	int GetX3() {return X3;}
	int GetCentreX() {return CentreX;}
	int GetY1() {return Y1;}
	int GetY2() {return Y2;}
	int GetY3() {return Y3;}
	int GetCentreY() {return CentreY;}
	void Tomber();
	void Dessiner();
	virtual void Rotation()=0;
	void Translate(int x,int y);
	void BougerAGauche();
	void BougerADroite();
};

#endif