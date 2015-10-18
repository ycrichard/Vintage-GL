#include "BrickT.h"
#include "box.h"
#include <cstdlib>

extern box** matrice;

BrickT::BrickT():BrickBase()
{
	X1=CentreX-1;
	Y1=CentreY;
	X2=CentreX;
	Y2=CentreY-1;
	X3=CentreX+1;
	Y3=CentreY;
	couleur=rose;
	
	oriente=1;
	switch(rand()%4)
	{
	case 0:Rotation();
	case 1:Rotation();
	case 2:Rotation();Translate(0,-1);
	case 3:break;
	}
}

void BrickT::Rotation()
{
	switch(oriente)
	{
	case 1:{
		if(!matrice[CentreY+5][CentreX+1].GetAppear())
		{
			X1=CentreX;
			Y1=CentreY-1;
			X2=CentreX+1;
			Y2=CentreY;
			X3=CentreX;
			Y3=CentreY+1;
			//Translate(-1,0);
			oriente++;
		}
		   break;}
	case 2:{
		if(!matrice[CentreY+4][CentreX].GetAppear())
		{
			X1=CentreX+1;
			Y1=CentreY;
			X2=CentreX;
			Y2=CentreY+1;
			X3=CentreX-1;
			Y3=CentreY;
			//Translate(1,-1);
			oriente++;
		}
		   break;}
	case 3:{
		if(!matrice[CentreY+3][CentreX+1].GetAppear())
		{
			X1=CentreX;
			Y1=CentreY+1;
			X2=CentreX-1;
			Y2=CentreY;
			X3=CentreX;
			Y3=CentreY-1;
			//Translate(0,1);
			oriente++;
		}
		   break;}
	case 4:{
		if(!matrice[CentreY+4][CentreX+2].GetAppear())
		{
			X1=CentreX-1;
			Y1=CentreY;
			X2=CentreX;
			Y2=CentreY-1;
			X3=CentreX+1;
			Y3=CentreY;
			oriente=1;
		}
		   break;}
	}
	//oriente++;
	//if(oriente>4) oriente=1;

}

