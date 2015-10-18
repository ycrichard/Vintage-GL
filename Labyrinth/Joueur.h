#ifndef Joueur_h
#define Joueur_h
#include "PersonnageBase.h"

class Joueur: public PersonnageBase
{

public:

	Joueur():PersonnageBase()	{}
	void Dessiner();
};

#endif