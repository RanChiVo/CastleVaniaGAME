#include "WallChangingMap.h"
#include "GameObjects/Simon.h"
#include "MovingMap.h"

WallChangingMap::WallChangingMap()
{
	id = ID_ENTITY_WALL_CHANGINGMAP;
}

void WallChangingMap::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void WallChangingMap::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void WallChangingMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		if (name.compare("Reset Viewport") == 0)
		{
			Direct3DManager::getInstance()->getViewport()->setStartViewPortX(getStartViewPort());
			Direct3DManager::getInstance()->getViewport()->setEndViewPortX(getEndViewPort());
		}

		if (name.compare("Reset Position") == 0)
		{
			Simon::getInstance()->setIdHiddenItem(getIdHiddenItem());
			Simon::getInstance()->setResetPosition(D3DXVECTOR2(x, y));
			Simon::getInstance()->setStartViewPort(getStartViewPort());
			Simon::getInstance()->setEndViewPort(getEndViewPort());
		}

		if (name.compare("StartInsideCastle") == 0)
		{
			MovingMap::getInstance()->setIdMap(ID_ENTITY_MAP_PLAYGAME);
			Simon::getInstance()->SetPosition(D3DXVECTOR2(0, 336.f));
		}

		if (Simon::getInstance()->IsOnStair())
		{
			if (Simon::getInstance()->GetState() == Simon::SIMON_STATE_GO_DOWN_STAIR || Simon::getInstance()->GetState() == Simon::SIMON_STATE_IDLE_DOWN_STAIR
				|| Simon::getInstance()->GetState() == Simon::SIMON_STATE_ATTACK_DOWN_STAIR)
			
			{
				if (name.compare("MoveDownUnderGroundFirst") == 0)
				{
					Simon::getInstance()->getOriginalStair()->SetPosition(D3DXVECTOR2(179.17f, 175.f));
					Simon::getInstance()->getOriginalStair()->set_nx(-1);
					Simon::getInstance()->getOriginalStair()->set_ny(1);
					Simon::getInstance()->SetPosition(D3DXVECTOR2(15.f, -20.f));	
					MovingMap::getInstance()->setIdMap(ID_ENTITY_MAP_UNDERGROUND);
				}
				else if (name.compare("MoveDownUnderGroundSecond") == 0)
				{
					Simon::getInstance()->getOriginalStair()->SetPosition(D3DXVECTOR2(894.50f, 239.f));
					Simon::getInstance()->getOriginalStair()->set_nx(-1);
					Simon::getInstance()->getOriginalStair()->set_ny(1);
					Simon::getInstance()->SetPosition(D3DXVECTOR2(698.17f, 26));
					MovingMap::getInstance()->setIdMap(ID_ENTITY_MAP_UNDERGROUND);
				}
				else if (name.compare("ResetViewportDownStair") == 0)
				{
					Direct3DManager::getInstance()->getViewport()->setStartViewPortX(getStartViewPort());
					Direct3DManager::getInstance()->getViewport()->setEndViewPortX(getEndViewPort());
				}
			}

			if (Simon::getInstance()->GetState() == Simon::SIMON_STATE_GO_UP_STAIR || Simon::getInstance()->GetState() == Simon::SIMON_STATE_IDLE_UP_STAIR
				|| Simon::getInstance()->GetState() == Simon::SIMON_STATE_ATTACK_UP_STAIR)
			{
				if (name.compare("MoveUpInsideFirst") == 0)
				{
					Simon::getInstance()->getOriginalStair()->SetPosition(D3DXVECTOR2(3150.92f, 380));
					Simon::getInstance()->getOriginalStair()->set_ny(-1);
					Simon::getInstance()->getOriginalStair()->set_nx(1);
					Simon::getInstance()->SetPosition(D3DXVECTOR2(3180.0f, 410.0f));
					MovingMap::getInstance()->setIdMap(ID_ENTITY_MAP_PLAYGAME);
				}
				else if (name.compare("MoveUpInsideSecond") == 0)
				{
					Simon::getInstance()->getOriginalStair()->SetPosition(D3DXVECTOR2(3150.92f, 395));
					Simon::getInstance()->getOriginalStair()->set_ny(-1);
					Simon::getInstance()->getOriginalStair()->set_nx(1);
					Simon::getInstance()->SetPosition(D3DXVECTOR2(3820, 410.0f));
					MovingMap::getInstance()->setIdMap(ID_ENTITY_MAP_PLAYGAME);
				}
				else if (name.compare("ResetViewportUpStair") == 0)
				{
					Direct3DManager::getInstance()->getViewport()->setStartViewPortX(getStartViewPort());
					Direct3DManager::getInstance()->getViewport()->setEndViewPortX(getEndViewPort());
				}
				
			}
		
		}
	}
}


WallChangingMap::~WallChangingMap()
{
}
