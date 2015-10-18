#ifndef box_h
#define box_h

#include <iostream>
using namespace std;
#include "GL/glut.h"
#include "color.h"

class box
{
private:
	bool appear;
	COLOR couleur;
	int X,Y;
public:
	box(){appear=false; couleur=gris;}
	void Dessiner();
	bool GetAppear() {return appear;}
	COLOR GetCouleur() {return couleur;}
	int GetX() {return X;}
	int GetY() {return Y;}
	void SetAppear(bool b) {appear=b;}
	void SetCouleur(COLOR c) {couleur=c;}
	void SetXY(int x,int y) {X=x;Y=y;}
};

#endif