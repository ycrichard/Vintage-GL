#ifndef EnnemiRouge_h
#define EnnemiRouge_h
#include "EnnemiBase.h"

class EnnemiRouge: public EnnemiBase
{

public:
	EnnemiRouge():EnnemiBase()	{}
	void DeplacementAuto();
	void Dessiner();
};

#endif