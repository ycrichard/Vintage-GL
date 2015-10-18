#ifndef EnnemiVert_h
#define EnnemiVert_h
#include "EnnemiBase.h"

class EnnemiVert: public EnnemiBase
{

public:
	EnnemiVert():EnnemiBase() {}
	void DeplacementAuto() { EnnemiBase::DeplacementAuto(); }
	void Dessiner();
};

#endif