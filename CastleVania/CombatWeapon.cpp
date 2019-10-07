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
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (getLevel() == 0)
		{
			switch (coObjects->at(i)->getID())
			{
				case ID_TEX_BURNBARREL:
					float left1, top1, right1, bottom1;
					coObjects->at(i)->GetBoundingBox(left1, top1, right1, bottom1);
					RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };

					float left2, top2, right2, bottom2;
					this->GetBoundingBox(left2, top2, right2, bottom2);
					RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };

					bool result = this->checkCollision(rect1, rect2);

					if (result)
					{
						coObjects->at(i)->SetState(STATE_FIRE);
						coObjects->at(i)->setLiveTime(GetTickCount());
					}
					break;
			}
		}
		else if(getLevel() == 1) {

			switch (coObjects->at(i)->getID())
			{
			case ID_TEX_ZOMBIE:
			case ID_TEX_CANDLE:

				float left1, top1, right1, bottom1;
				coObjects->at(i)->GetBoundingBox(left1, top1, right1, bottom1);
				RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };

				float left2, top2, right2, bottom2;
				this->GetBoundingBox(left2, top2, right2, bottom2);
				RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };

				bool result = this->checkCollision(rect1, rect2);

				if (result)
				{
					coObjects->at(i)->SetState(STATE_FIRE);
				}
				break;
			}
		}
	}
}
	

