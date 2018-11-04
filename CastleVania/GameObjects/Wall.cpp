#include "Wall.h"


Wall::Wall(int l, int t, int r, int b)
{
	boundingBox.left = l;
	boundingBox.top = t;
	boundingBox.right = r;
	boundingBox.bottom = b;
}

RECT Wall::getBounding()
{
	return boundingBox;
}

Wall::~Wall()
{
}
