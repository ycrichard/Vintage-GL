#include "BrickBase.h"

class BrickI:public BrickBase
{
private:
	int oriente;
public:
	BrickI();
	void Rotation();
};