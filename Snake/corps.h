#include <iostream>
using namespace std;
#include "GL/freeglut.h"

enum DIRECTION { haut,bas,gauche,droite};

class corps
{
private:
	int PosC;
	int PosL;
	DIRECTION Dir;
public:
	corps() { PosC=0; PosL=0; Dir=droite;}
	int GetPosC() { return PosC;}
	int GetPosL() { return PosL;}
	DIRECTION GetDir() { return Dir;}
	void SetDir(DIRECTION d) { Dir=d;}
	void SetPosC(int C) { PosC=C; }
	void SetPosL(int L) {PosL=L; }
	void Bouger();
	void TestCollision();
	void SeCollision(corps* c);
	void Dessiner();
	void Suivre(corps* c);
};