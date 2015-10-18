#include "BrickI.h"
#include "box.h"
#include <cstdlib>

extern int NbColonnes;
extern int NbLignes;
extern box** matrice;

BrickI::BrickI():BrickBase()
{
	X1=CentreX-2;
	Y1=CentreY;
	X2=CentreX-1;
	Y2=CentreY;
	X3=CentreX+1;
	Y3=CentreY;
	couleur=aqua;

	oriente=1;
	switch(rand()%2)
	{
	case 0:Rotation();Translate(0,-2);
	case 1:break;
	}
}

void BrickI::Rotation()
{
	switch(oriente)
	{
	case 1:{
		if(CentreY==NbLignes-1) break;
		else if(!matrice[CentreY+5][CentreX+1].GetAppear() && !matrice[CentreY+6][CentreX+1].GetAppear())
		{
			X1=CentreX;
			Y1=CentreY-1;
			X2=CentreX;
			Y2=CentreY+1;
			X3=CentreX;
			Y3=CentreY+2;
			oriente=2;
		}
			break;}
	case 2:{
		if(CentreX==0) break;
		else if(!matrice[CentreY+4][CentreX-1].GetAppear() && !matrice[CentreY+4][CentreX].GetAppear() && !matrice[CentreY+4][CentreX+2].GetAppear())
		{
			X1=CentreX-2;
			Y1=CentreY;
			X2=CentreX-1;
			Y2=CentreY;
			X3=CentreX+1;
			Y3=CentreY;
			oriente=1;}
		break;}
	}
}