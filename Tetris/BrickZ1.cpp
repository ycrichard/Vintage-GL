#include "BrickZ1.h"
#include "box.h"
#include <cstdlib>

extern box** matrice;

BrickZ1::BrickZ1():BrickBase()
{
	X1=CentreX-1; Y1=CentreY-1;
	X2=CentreX;   Y2=CentreY-1;
	X3=CentreX+1; Y3=CentreY;
	couleur=rouge;

	oriente=1;
	switch(rand()%2)
	{
	case 0:Rotation();Translate(0,-1);
	case 1:break;
	}
}

void BrickZ1::Rotation()
{
	switch(oriente)
	{
	case 1:{
		if(!matrice[CentreY+4][CentreX].GetAppear() && !matrice[CentreY+5][CentreX].GetAppear())
		{
			X1=CentreX+1;Y1=CentreY-1;
			X2=CentreX+1;Y2=CentreY;
			X3=CentreX;  Y3=CentreY+1;
			Translate(-1,0);

			oriente=2;
		}
		break;}
	case 2:{
		if(!matrice[CentreY+3][CentreX+1].GetAppear() && !matrice[CentreY+4][CentreX+3].GetAppear())
		{
			X1=CentreX-1; Y1=CentreY-1;
			X2=CentreX;   Y2=CentreY-1;
			X3=CentreX+1; Y3=CentreY;
			Translate(1,0);

			oriente=1;
		}
		break;}
	}
}