#include "BrickE.h"

BrickE::BrickE():BrickBase()
{
	X1=CentreX+1;
	Y1=CentreY;
	X2=CentreX+1;
	Y2=CentreY-1;
	X3=CentreX;
	Y3=CentreY-1;
	couleur=jaune;
}