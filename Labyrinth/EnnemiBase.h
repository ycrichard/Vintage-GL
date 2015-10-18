#ifndef EnnemiBase_h
#define EnnemiBase_h
#include "PersonnageBase.h"

class EnnemiBase: public PersonnageBase
{
protected:
	EnnemiBase* suivant;
public:
	EnnemiBase():PersonnageBase()	{ suivant=NULL; }
	virtual void DeplacementAuto();
	void TestCollision();
	EnnemiBase* GetSuivant();
	void SetSuivant(EnnemiBase* e);
};

#endif