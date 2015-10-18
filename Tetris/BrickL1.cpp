#include "BrickL1.h"
#include "box.h"
#include <cstdlib>

extern box** matrice;

BrickL1::BrickL1():BrickBase()
{
	X1=CentreX-1;Y1=CentreY;
	X2=CentreX+1;Y2=CentreY-1;
	X3=CentreX+1;Y3=CentreY;
	couleur=orange;

	oriente=1;
	switch(rand()%4)
	{
	case 0:Rotation();
	case 1:Rotation();
	case 2:Rotation();Translate(0,-1);
	case 3:break;
	}
}

void BrickL1::Rotation()
{
	switch(oriente)
	{
	case 1:{
		if(!matrice[CentreY+3][CentreX+1].GetAppear() && !matrice[CentreY+5][CentreX+2].GetAppear() && !matrice[CentreY+5][CentreX+1].GetAppear())
		{
			X1=CentreX;  Y1=CentreY-1;
			X2=CentreX+1;Y2=CentreY+1;
			X3=CentreX;  Y3=CentreY+1;

			oriente++;
		}
		break;}
	case 2:{
		if(!matrice[CentreY+4][CentreX+2].GetAppear() && !matrice[CentreY+5][CentreX].GetAppear() && !matrice[CentreY+4][CentreX].GetAppear())
		{
			X1=CentreX+1;Y1=CentreY;
			X2=CentreX-1;Y2=CentreY+1;
			X3=CentreX-1;Y3=CentreY;

			oriente++;
		}
		break;}
	case 3:{
		if(!matrice[CentreY+5][CentreX+1].GetAppear() && !matrice[CentreY+3][CentreX].GetAppear() && !matrice[CentreY+3][CentreX+1].GetAppear())
		{
			X1=CentreX;  Y1=CentreY+1;
			X2=CentreX-1;Y2=CentreY-1;
			X3=CentreX;  Y3=CentreY-1;

			oriente++;
		}
		break;}
	case 4:{
		if(!matrice[CentreY+4][CentreX].GetAppear() && !matrice[CentreY+3][CentreX+2].GetAppear() && !matrice[CentreY+4][CentreX+2].GetAppear())
		{
			X1=CentreX-1;Y1=CentreY;
			X2=CentreX+1;Y2=CentreY-1;
			X3=CentreX+1;Y3=CentreY;

			oriente=1;
		}
		break;}
	}
}