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
		case ID_ENTITY_VAMPIRE_BAT:
		case ID_ENTITY_FISH_MAN:
		
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
				DebugOut(L"liveTime:{%d}\n", coObjects->at(i)->getLiveTime());
				if (id == ID_ENTITY_DAGGER_WEAPON)
					SetState(STATE_DETROY);
			}
			break;
		}
	}
}


