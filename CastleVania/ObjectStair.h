#include "StaticObject.h"

#pragma once
class ObjectStair :public StaticObject
{
	int heightStair;
	int nxStair;
	int nyStair;
	bool isTwoDirection;
public:
	ObjectStair(D3DXVECTOR2 pos, int width, int height, int nx, int ny, int heightStair, bool isTwoDirection);
	//ObjectStair(ObjectStair* o);
	int GetHeightStair() { return heightStair; }
	void SetHeightStair(int heightStair) { this->heightStair = heightStair; }
	void Set_nxStair(int nx) { this->nxStair = nx; }
	void Set_nyStair(int ny) { this->nyStair = ny; }
	void Set_IsTwoDirection(int isTwoDirection) { this->isTwoDirection = isTwoDirection; }
	
	bool IsTwoDirection() { return isTwoDirection; }
	int Get_nxStair() { return nxStair; }
	int Get_nyStair() { return nyStair; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	~ObjectStair();
};

