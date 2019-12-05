#include "CombatWeapon.h"


CombatWeapon::CombatWeapon()
{

}

CombatWeapon::~CombatWeapon()
{

}

void CombatWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	for (int i = 0; i < coObjects->size(); i++)
	{
		int ID = coObjects->at(i)->getID();
		switch (ID)
		{
		case ID_ENTITY_BURNBARREL:
		case ID_ENTITY_CANDLE:
		case ID_ENTITY_ZOMBIE:
		case ID_ENTITY_PANTHER:
		case ID_ENTITY_BRICK:
		
			float left1, top1, right1, bottom1;
			coObjects->at(i)->GetBoundingBox(left1, top1, right1, bottom1);
			RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };

			float left2, top2, right2, bottom2;

			GetBoundingBox(left2, top2, right2, bottom2);

			RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };

			bool result = this->checkCollision(rect1, rect2);

			if (result)
			{
				coObjects->at(i)->SetState(STATE_EFFECT);
				coObjects->at(i)->setLiveTime(GetTickCount());
				if (id == ID_ENTITY_DAGGER_WEAPON)
					SetState(STATE_DETROY);
			}
			break;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != STATE_DETROY)
	CalcPotentialCollisions(coObjects, coEvents);

	float min_tx, min_ty, nx, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (int i = 0; i < (int)coEvents.size(); i++)
	{
		switch (coEvents[i]->obj->getID())
		{
		case ID_ENTITY_ZOMBIE:
		case ID_ENTITY_PANTHER:
			coEvents[i]->obj->SetState(STATE_EFFECT);
			coEvents[i]->obj->setLiveTime(GetTickCount());
			break;
		case ID_ENTITY_FLOOR:
			if ((coEvents[i]->obj->getName().compare("Floor") == 0))
			{
				y += min_ty * dy + ny * 0.1f;
				SetState(STATE_DETROY);
			}
			break;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


