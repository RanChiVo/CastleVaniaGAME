#include "CombatWeapon.h"
#include "DarkBat.h"
#include "Ghost.h"
#include "SpearKnight.h"

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

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			switch (coEventsResult[i]->obj->getID())
			{
			case ID_ENTITY_FLEAMEN:
			case ID_ENTITY_WHITE_SKELETON:
			case ID_ENTITY_ZOMBIE:
			case ID_ENTITY_VAMPIRE_BAT:
			{
				if (coEventsResult[i]->obj->GetState() != STATE_EFFECT)
				{
					coEventsResult[i]->obj->SetVx(0);
					coEventsResult[i]->obj->SetState(STATE_EFFECT);
					coEventsResult[i]->obj->setLiveTime(GetTickCount());
				}
			}
				break;
			case ID_ENTITY_GHOST:
			{
				Ghost* ghost = dynamic_cast<Ghost*>(coObjects->at(i));
				if (ghost)
				{
					if (ghost->GetState() != STATE_EFFECT)
					{
						if (ghost->GetTimeHurt() == 0)
						{
							ghost->SetTimeHurt(GetTickCount());
						}
					}
				}
			}
				break;
			case ID_ENTITY_SPEAR_KNIGHT:
			{
				SpearKnight *spearKnight = dynamic_cast<SpearKnight *>((coObjects->at(i)));
				if (spearKnight)
				{
					if (spearKnight->GetState() != STATE_EFFECT)
					{
						if (spearKnight->GetTimeHurt() == 0)
						{
							spearKnight->SetTimeHurt(GetTickCount());
							spearKnight->SetSpeed(0, 0);
						}
					}
				}
			}
				break;
			case ID_ENTITY_DARK_BAT:
				DarkBat::StartTimeHurt();
				break;
			}
		}
		x += Dx;
		y += Dy;
	}

	for (int i = 0; i < coObjects->size(); i++)
	{
		int ID = coObjects->at(i)->getID();
		switch (ID)
		{
		case ID_ENTITY_BURNBARREL:
		case ID_ENTITY_CANDLE:
		case ID_ENTITY_BRICK:
		case ID_ENTITY_FLEAMEN:
		case ID_ENTITY_WHITE_SKELETON:
		case ID_ENTITY_ZOMBIE:
		case ID_ENTITY_VAMPIRE_BAT:
		case ID_ENTITY_GHOST:
		case ID_ENTITY_SPEAR_KNIGHT:
		case ID_ENTITY_DARK_BAT:
			float left1, top1, right1, bottom1;
			coObjects->at(i)->GetBoundingBox(left1, top1, right1, bottom1);
			RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };

			float left2, top2, right2, bottom2;

			GetBoundingBox(left2, top2, right2, bottom2);

			RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };

			bool result = this->checkCollision(rect1, rect2);

			if (result)
			{
				switch (ID)
				{
				case ID_ENTITY_DARK_BAT:
					DarkBat::StartTimeHurt();
					break;
				case ID_ENTITY_BRICK:
					if (coObjects->at(i)->getName().compare("EdgeBrick") != 0)
					{
						if (coObjects->at(i)->GetState() != STATE_EFFECT)
						{
							coObjects->at(i)->SetSpeed(0, 0);
							coObjects->at(i)->SetState(STATE_EFFECT);
							coObjects->at(i)->setLiveTime(GetTickCount());
						}
					}
					break;
				case ID_ENTITY_GHOST:
				{
					Ghost* ghost = dynamic_cast<Ghost*>(coObjects->at(i));
					if (ghost)
					{
						if (ghost->GetState() != STATE_EFFECT)
						{
							if (ghost->GetTimeHurt() == 0)
							{
								ghost->SetTimeHurt(GetTickCount());
							}
						}
					}
				}
					break;
				case ID_ENTITY_SPEAR_KNIGHT:
				{
					SpearKnight *spearKnight = dynamic_cast<SpearKnight *>((coObjects->at(i)));
					if (spearKnight)
					{
						if (spearKnight->GetState() != STATE_EFFECT)
						{
							if (spearKnight->GetTimeHurt()==0)
							{
								spearKnight->SetTimeHurt(GetTickCount());
								spearKnight->SetSpeed(0, 0);
							}
						}
					}
				}
					break;
				default:
					if (coObjects->at(i)->GetState() != STATE_EFFECT)
					{
						coObjects->at(i)->SetSpeed(0, 0);
						coObjects->at(i)->SetState(STATE_EFFECT);
						coObjects->at(i)->setLiveTime(GetTickCount());
					}
					break;
				}
			}
			break;
		}
	}
}


