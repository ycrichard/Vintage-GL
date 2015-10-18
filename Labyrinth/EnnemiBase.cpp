#include "EnnemiBase.h"

#include "Joueur.h"
extern Joueur MonJoueur;
extern void LibererMemoire();
extern void LabyAffichage();

/*void EnnemiBase::DeplacementAuto()
{
	int hasard = rand()%4;
	switch(hasard)
	{
	case 0:{
		BougerEnHaut();
		break;}
	case 1:{
		BougerEnBas();
		break;}
	case 2:{
		BougerAGauche();
		break;}
	case 3:{
		BougerADroite();
		break;}
	}
}*/
void EnnemiBase::DeplacementAuto()
{

	if(MonJoueur.GetPosC()-PosC>=0 && MonJoueur.GetPosC()-PosC<=3 && MonJoueur.GetPosL()-PosL>=0 && MonJoueur.GetPosL()-PosL<=3)
	{
			int hasard = rand()%2;
			switch(hasard)
			{
			case 0:{ BougerEnBas(); break;}
			case 1:{ BougerADroite(); break;}
			}
	}
	else if(MonJoueur.GetPosC()-PosC>=0 && MonJoueur.GetPosC()-PosC<=3 && MonJoueur.GetPosL()-PosL>=-3 && MonJoueur.GetPosL()-PosL<0)
	{
			int hasard = rand()%2;
			switch(hasard)
			{
			case 0:{ BougerEnHaut(); break;}
			case 1:{ BougerADroite(); break;}
			}
	}
	else if(MonJoueur.GetPosC()-PosC<0 && MonJoueur.GetPosC()-PosC>=-3 && MonJoueur.GetPosL()-PosL<=3 && MonJoueur.GetPosL()-PosL>=0)
	{
			int hasard = rand()%2;
			switch(hasard)
			{
			case 0:{ BougerEnBas(); break;}
			case 1:{ BougerAGauche(); break;}
			}
	}
	else if(MonJoueur.GetPosC()-PosC<0 && MonJoueur.GetPosC()-PosC>=-3 && MonJoueur.GetPosL()-PosL>=-3 && MonJoueur.GetPosL()-PosL<0)
	{
			int hasard = rand()%2;
			switch(hasard)
			{
			case 0:{ BougerEnHaut(); break;}
			case 1:{ BougerAGauche(); break;}
			}
	}
	else
	{
		int hasard = rand()%4;
		switch(hasard)
		{
		case 0:{
			BougerEnHaut();
			break;}
		case 1:{
			BougerEnBas();
			break;}
		case 2:{
			BougerAGauche();
			break;}
		case 3:{
			BougerADroite();
			break;}
		}
	}

}


void EnnemiBase::TestCollision()
{
	if(PosC==MonJoueur.GetPosC() && PosL==MonJoueur.GetPosL())
	{
		LabyAffichage();
		glutExit();
		LibererMemoire();
		cout<<"You lose !"<<endl;
		//system("pause");
		exit(0);
	}
}

EnnemiBase* EnnemiBase::GetSuivant()
{
	return suivant;
}
void EnnemiBase::SetSuivant(EnnemiBase* e)
{
	suivant=e;
}
