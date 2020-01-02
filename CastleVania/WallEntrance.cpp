#include "WallEntrance.h"
#include "GameObjects/Simon.h"


WallEntrance::WallEntrance()
{
	id = ID_ENTITY_WALL_ENTRANCE;
}

void WallEntrance::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void WallEntrance::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	float left1, top1, right1, bottom1;
	Simon::getInstance()->GetBoundingBox(left1, top1, right1, bottom1);
	RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };
	float left2, top2, right2, bottom2;
	GetBoundingBox(left2, top2, right2, bottom2);
	RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };

	bool result = this->checkCollision(rect1, rect2);
	if (result)
	{
		if (name.compare(""))
		{

		}
	}
}

void WallEntrance::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (name.compare("WallEndMap")==0 )
	{
		if (!Simon::getInstance()->isMovedEndMap())
		{
			l = t = r = b = 0;
		}
		else
		{
			l = x;
			t = y;
			r = x + width;
			b = y + height;
		}
	}
	else 
	{
		l = x;
		t = y;
		r = x + width;
		b = y + height;
	}
}

WallEntrance::~WallEntrance()
{
}
