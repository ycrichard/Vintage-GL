#ifndef PersonnageBase_h
#define PersonnageBase_h
#include <iostream>
using namespace std;
#include "GL/freeglut.h"

class PersonnageBase
{
protected:
	int PosC;
	int PosL;
public:
	int GetPosC() const { return PosC; }
	int GetPosL() const { return PosL; }
	PersonnageBase()	{ PosC=0; PosL=0;}
	virtual void Dessiner()=0;
	void SetPosC(int C) { PosC = C; }
	void SetPosL(int L) { PosL = L; }
	void BougerEnHaut();
	void BougerEnBas();
	void BougerAGauche();
	void BougerADroite();
};

#endif
