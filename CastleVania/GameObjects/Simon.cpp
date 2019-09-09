#include "Simon.h"
#include "BurnBarrel.h"
#include "../GameObjects/Heart.h"
#include "../GameObjects/WeaponReward.h"	
#include "../GameObjects/MiraculousBag.h"
#include "../GameObjects/Katana.h"
#include "../GameObjects/Floor.h"
#include "../PodiumOnWall.h"
#include "../GameObjects/Cross.h"
#include "../GameObjects/SmallHeart.h"
#include "../GameObjects/FireBomb.h"
#include "../GameObjects/StopWatch.h"
#include "../Candle.h"
#include "../Brick.h"
#include "../GameObjects/Entrance.h"
#include "../EntityID.h"
#include "../Flip.h"
#include "../GameObjects/Zombie.h"

constexpr float SIMON_MOVE_SPEED = 0.1f;
constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.42f;
constexpr float SIMON_GRAVITY = 0.0007f;
constexpr int SIMON_PROTECT_TIME = 2000;
constexpr float SIMON_UP_STAIR_SPEED_Y = 0.09f;
constexpr float SIMON_UP_STAIR_SPEED_X = 0.09f;
constexpr auto GROUND_POSITION = 289;
constexpr auto MAPSIZE_WIDTH = 1475;
constexpr auto P0SITION_ENTRANCE = 1300;
constexpr int SIMON_UNTOUCHABLE_TIME = 5000;
constexpr int SIMON_ENTRANCE_TIME = 3000;

Simon::Simon()
{
	id = ID_TEX_SIMON;
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);

	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	WHIP_STATE = 1;
	isChangeLevel = false;
	SetPosition(D3DXVECTOR2(0, 0));
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DirectInput* directInput = DirectInput::getInstance();

	GameObject::Update(dt, coObjects);

	objectCollision.clear();
	objectItem.clear();
	enemyList.clear();

	if (!isChangeLevel)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_TEX_HEART:
			case ID_TEX_WEAPON_REWARD:
			case ID_TEX_KATANA:
				objectItem.push_back(coObjects->at(i));
				break;
			case ID_TEX_BURNBARREL:
				objectCollision.push_back(coObjects->at(i));
				break;
			}
		}
	}
	else if (isChangeLevel)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_TEX_HEART:
			case ID_TEX_WEAPON_REWARD:
			case ID_TEX_SMALL_HEART:
			case ID_TEX_CROSS:
			case ID_TEX_FIRE_BOMB:
			case ID_TEX_MIRACULOUS_BAG:
				objectItem.push_back(coObjects->at(i));
				break;
			case ID_TEX_CANDLE:
			case ID_COLLISION_STAIR:
				objectCollision.push_back(coObjects->at(i));
				break;
			case ID_TEX_ZOMBIE:
				enemyList.push_back(coObjects->at(i));
				break;
			}

		}
	}

	handleState();

	if (isChangeLevel == false)
	{
		if (GetTickCount() - comeEntranceStart <= SIMON_ENTRANCE_TIME)
			SetState(SIMON_STATE_WALKING_RIGHT);
		else if (comeEntranceStart > 0)
			comeEntranceStart = 0;
	}

	vy += SIMON_GRAVITY * dt;

	for (int i = 0; i < objectCollision.size(); i++)
	{
		if (objectCollision.at(i)->getID() == ID_COLLISION_STAIR)
		{
			float l, t, r, b;
			objectCollision.at(i)->GetBoundingBox(l, t, r, b);
			RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

			float L, T, R, B;
			GetBoundingBox(L, T, R, B);
			RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

			bool result = checkCollision(rect2, rect1);


			if (result)
			{
				if (directInput->IsKeyDown(DIK_UP) && objectCollision.at(i)->getIdHiddenItem() == "right-up")
				{
					SetState(SIMON_STATE_GO_UP_STAIR_RIGHT);
					isOnStair = true;
				}
				else if (directInput->IsKeyDown(DIK_DOWN) && objectCollision.at(i)->getIdHiddenItem() == "left-down")
				{
					SetState(SIMON_STATE_GO_DOWN_STAIR_LEFT);
					isOnStair = true;
				}
				else if (isOnStair && objectCollision.at(i)->getIdHiddenItem() == "right-up-idle")
				{
					SetState(SIMON_STATE_IDLE);
					isOnStair = false;
				}
				/*else if (isOnStair && objectCollision.at(i)->getIdHiddenItem() == "left-down-idle")
				{
					SetState(SIMON_STATE_IDLE);
					isOnStair = false;
				}*/
			}
			else
			{
				if (state == SIMON_STATE_IDLE_ON_STAIR)
				{
					if (directInput->IsKeyDown(DIK_UP))
					{
						SetState(SIMON_STATE_GO_UP_STAIR_RIGHT);
						isOnStair = true;
					}
					else if (directInput->IsKeyDown(DIK_DOWN))
					{
						SetState(SIMON_STATE_GO_DOWN_STAIR_LEFT);
						isOnStair = true;
					}
				}
			}

		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		if (attacking && DirectInput::getInstance()->IsKeyDown(DIK_UP) && itemList.size() != 0)
		{
			for (int i = 0; i < coObjects->size(); i++)
			{
				if (coObjects->at(i)->getID() == ID_TEX_KATANA_WEAPON)
				{
					if (nx == 1) coObjects->at(i)->SetState(KATANAWEAPON_STATE_RIGHT);
					else if (nx == -1) coObjects->at(i)->SetState(KATANAWEAPON_STATE_LEFT);
					coObjects->at(i)->SetPosition(D3DXVECTOR2(x, y));
				}
			}
		}

		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Zombie *>(e->obj))
			{
				if (e->nx != 0)
				{
					SetState(SIMON_STATE_HURT);
				}
			}
		}

		for (int i = 0; i < coEvents.size(); i++)
		{
			switch (coEvents[i]->obj->getID())
			{
			case ID_TEX_WALL:
				Dx = min_tx * dx + nx * 0.4f;
				if (nx != 0) vx = 0;
				break;
			case ID_TEX_ENTRANCE:
				comeEntranceStart = GetTickCount();
				DebugOut(L"inserted\n");
				break;
			case ID_TEX_WALL_ENTRANCE:
				isChangeLevel = true;
				x = 50;
				SetState(SIMON_STATE_IDLE);
				break;
			case ID_TEX_HEART:
				for (int j = 0; j < coObjects->size(); j++)
				{
					if (coObjects->at(j)->getID() == ID_TEX_HEART)
					{
						std::string a = coObjects->at(j)->getIdHiddenItem();
						std::string b = coEvents[i]->obj->getIdHiddenItem();
						if (a.compare(b) == 0)
						{
							coObjects->at(j)->SetState(HEART_STATE_HIDE);
							coObjects->erase(coObjects->begin() + j);
						}
					}
				}
				break;
			case ID_TEX_WEAPON_REWARD:
				for (int j = 0; j < coObjects->size(); j++)
				{
					std::string a = coObjects->at(j)->getIdHiddenItem();
					std::string b = coEvents[i]->obj->getIdHiddenItem();
					if (a.compare(b) == 0)
						if (coObjects->at(j)->getID() == ID_TEX_WEAPON_REWARD)
						{
							coObjects->at(j)->SetState(WEAPONREWARD_STATE_HIDE);
							coObjects->erase(coObjects->begin() + j);
						}
				}
				SetState(SIMON_STATE_CHANGECOLOR);
				if (level == 1)
				{
					level = 2;
				}
				else if (level == 2)
				{
					level = 3;
				}
				break;

			case ID_TEX_KATANA:
				for (int j = 0; j < coObjects->size(); j++)
				{
					std::string a = coObjects->at(j)->getIdHiddenItem();
					std::string b = coEvents[i]->obj->getIdHiddenItem();
					if (a.compare(b) == 0)
						if (coObjects->at(j)->getID() == ID_TEX_KATANA)
						{
							coObjects->at(j)->SetState(KATANA_STATE_HIDE);
							coObjects->erase(coObjects->begin() + j);
						}
				}
				break;

			case ID_TEX_MIRACULOUS_BAG:
				for (int j = 0; j < coObjects->size(); j++)
				{
					std::string a = coObjects->at(j)->getIdHiddenItem();
					std::string b = coEvents[i]->obj->getIdHiddenItem();
					if (a.compare(b) == 0)
						if (coObjects->at(j)->getID() == ID_TEX_MIRACULOUS_BAG)
						{
							coObjects->at(j)->SetState(MIRACULOUSBAG_STATE_HIDE);
							coObjects->erase(coObjects->begin() + j);
						}
				}
				break;

			case ID_TEX_SMALL_HEART:
				for (int j = 0; j < coObjects->size(); j++)
				{
					std::string a = coObjects->at(j)->getIdHiddenItem();
					std::string b = coEvents[i]->obj->getIdHiddenItem();
					if (a.compare(b) == 0)
						if (coObjects->at(j)->getID() == ID_TEX_SMALL_HEART)
						{
							coObjects->at(j)->SetState(SMALL_HEART_STATE_HIDE);
							coObjects->erase(coObjects->begin() + j);
						}
				}
				break;

			case ID_TEX_PODIUM_ON_WALL:
				Dy = min_ty * dy + ny * 0.4f;
				if (ny != 0) vy = 0;
				break;

			case ID_TEX_FLOOR:
				Dy = min_ty * dy + ny * 0.4f;
				if (ny != 0) vy = 0;
				break;

			case ID_TEX_BURNBARREL:
				break;

			case ID_TEX_CANDLE:
				break;

			}
		}
		x += Dx;
		y += Dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//for (UINT i = 0; i < coEventsResult.size(); i++)
	//{
	//	LPCOLLISIONEVENT e = coEventsResult[i];

	//	if (dynamic_cast<Entrance *>(e->obj))
	//	{
	//		if (e->nx != 0)
	//		{
	//		}
	//	}
	//	else if (dynamic_cast<CBrick *>(e->obj))
	//	{
	//		if (e->nx != 0)
	//		{
	//			Dx = min_tx * dx + nx * 1.0f;
	//			if (nx != 0) vx = 0;
	//		}

	//	}
	//	else if (dynamic_cast<Heart *>(e->obj))
	//	{
	//		Heart *heart = dynamic_cast<Heart *>(e->obj);

	//		if (e->nx != 0)
	//		{
	//			if (nx != 0) vx = 0;
	//			heart->SetPosition(D3DXVECTOR2(-100, -100));
	//		}
	//	}
	//	else if (dynamic_cast<WeaponReward *>(e->obj))
	//	{
	//		WeaponReward* weaponReward = dynamic_cast<WeaponReward *>(e->obj);
	//		if (e->nx != 0 || e->ny < 0)
	//		{
	//			if (nx != 0) vx = 0;
	//			weaponReward->SetPosition(D3DXVECTOR2(-100, -100));
	//			if (level == 1)
	//			{
	//				level = 2;
	//				SetState(SIMON_STATE_CHANGECOLOR1);
	//			}
	//			else if (level == 2)
	//			{
	//				level = 3;
	//				SetState(SIMON_STATE_CHANGECOLOR);
	//			}
	//		}

	//	}
	//	else if (dynamic_cast<Katana *>(e->obj))
	//	{
	//		Katana* katana = dynamic_cast<Katana *>(e->obj);
	//		if (e->nx != 0 || e->ny < 0)
	//		{
	//			if (nx != 0) vx = 0;

	//			katana->SetPosition(D3DXVECTOR2(-100, -100));
	//		}
	//	}
	//	else if (dynamic_cast<MiraculousBag *>(e->obj))
	//	{
	//		MiraculousBag*  miraculousBag = dynamic_cast<MiraculousBag *>(e->obj);
	//		if (e->nx != 0)
	//		{
	//			//miraculousBag->SetPosition(D3DXVECTOR2(-100, -100));
	//			Dx = min_tx * dx + nx * 1.0f;
	//			SetState(SIMON_STATE_WALKING_LEFT);
	//			for (int i = 0; i < coObjects->size(); i++)
	//			{
	//				if (coObjects->at(i)->getID() == ID_TEX_ENTRANCE)
	//				{
	//					//coObjects->at(i)->SetPosition(D3DXVECTOR2(127));
	//				}
	//			}
	//		}
	//	}
	//	else if (dynamic_cast<Floor *>(e->obj))
	//	{
	//		if (e->ny != 0)
	//		{
	//			Dy = min_ty * dy + ny * 1.0f;
	//		}
	//	}

	//	else if (dynamic_cast<BurnBarrel *>(e->obj))
	//	{

	//	}
	//}

/*	x += Dx;
	y += Dy;*/
	/*if (x > 1300)
	{
		SetState(SIMON_STATE_WALKING_RIGHT);
	}*/
	//}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_TEX_AREA_ZOMBIE)
		{
			float l, t, r, b;
			coObjects->at(i)->GetBoundingBox(l, t, r, b);
			RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };
			float L, T, R, B;
			GetBoundingBox(L, T, R, B);
			RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };
			if (rect1.left < rect2.left && rect1.bottom > rect2.bottom)
			{
				isCollision = true;
			}
			else isCollision = false;
		}
	}
}

void Simon::loadResource()
{
	AddAnimation(SIMON_ANI_IDLE);
	AddAnimation(SIMON_ANI_WALKING);
	AddAnimation(SIMON_ANI_JUMPING);
	AddAnimation(SIMON_ANI_SITDOWN);
	AddAnimation(SIMON_ANI_ATTACK_STANDING);
	AddAnimation(SIMON_ANI_ATTACK_SITDOWN);
	AddAnimation(SIMON_ANI_COLOR);
	AddAnimation(SIMON_ANI_COLOR1);
	AddAnimation(SIMON_ANI_GO_STAIR);
	AddAnimation(SIMON_ANI_IDLE_STAIR);
	AddAnimation(SIMON_ANI_HURT);
}

void Simon::SetState(int state)
{
	this->state = state;
}

void Simon::OnKeyStateChange(BYTE * states)
{
	DirectInput* directInput = DirectInput::getInstance();

	switch (state)
	{
	case SIMON_STATE_IDLE:
		if (directInput->IsKeyDown(DIK_K))
		{
			SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else if (directInput->IsKeyDown(DIK_H))
		{
			SetState(SIMON_STATE_WALKING_LEFT);
		}
		else if (directInput->IsKeyDown(DIK_J) && isOnGround())
		{
			SetState(SIMON_STATE_SITDOWN);
		}
		break;

	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (directInput->IsKeyDown(DIK_J) && isOnGround())
		{
			SetState(SIMON_STATE_SITDOWN);
		}
		break;
	}
}

void Simon::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	DirectInput* directInput = DirectInput::getInstance();

	switch (state)
	{
	case SIMON_STATE_IDLE:
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
	case SIMON_STATE_IDLE_ON_STAIR:
		if (KeyCode == DIK_X)
			SetState(SIMON_STATE_JUMPING);
		else if (KeyCode == DIK_Z || directInput->IsKeyDown(DIK_J) && KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_STAND);
		}
	case SIMON_STATE_JUMPING:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_JUMP);
		}
		if (KeyCode == DIK_J)
		{
			SetState(SIMON_STATE_IDLE);
		}
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_SITDOWN);
		}
		break;
	}
}

void Simon::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		if (KeyCode == DIK_K)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (KeyCode == DIK_H)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_J)
			SetState(SIMON_STATE_IDLE);
		break;
	}
}

vector<LPGAMEOBJECT> Simon::getItemList()
{
	return itemList;
}

int Simon::getWidthWorld()
{
	return 0;
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_SIMON)->Get("Walking4")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void Simon::Render(Viewport* viewport)
{
//	RenderBoundingBox(viewport);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	LPANIMATION animation = animations.find(currentAnimation)->second;

	if (animation != nullptr)
	{
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;
		animation->Render(pos.x, pos.y, flip);

		if (attacking && !(DirectInput::getInstance()->IsKeyDown(DIK_UP)))
		{
			whip = new Whip(D3DXVECTOR2(x, y));
			if (level == 1)
			{
				whip->SetState(WHIT_STATE_1);
			}
			else if (level == 2)
			{
				whip->SetState(WHIT_STATE_2);
			}
			else if (level == 3)
			{
				whip->SetState(WHIT_STATE_3);
			}
			whip->updatePostision(animation->getCurrentFrame(), currentAnimation, nx);
			whip->draw(nx, viewport);
			if (whip->getframe() == 2) whip->animations.find(currentAnimation)->second->SetFinish(true);

			if (!isChangeLevel)
			{
				for (int i = 0; i < objectCollision.size(); i++)
				{
					if (objectCollision[i]->getID() == ID_TEX_BURNBARREL)
					{
						float l, t, r, b;
						objectCollision[i]->GetBoundingBox(l, t, r, b);
						RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

						float L, T, R, B;
						whip->GetBoundingBox(L, T, R, B);
						RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

						bool result = whip->checkCollision(rect1, rect2);

						if (result)
						{
							D3DXVECTOR2 pos = objectCollision[i]->getPosition();

							objectCollision[i]->SetState(BURN_STATE_HIDE);

							std::string a = objectCollision[i]->getIdHiddenItem();

							for (int j = 0; j < objectItem.size(); j++)
							{
								std::string b = objectItem[j]->getIdHiddenItem();
								if (a.compare(b) == 0)
								{
									switch (objectItem[j]->getID())
									{
									case ID_TEX_HEART:
										objectItem[j]->SetState(HEART_STATE_SHOW);
										objectItem[j]->SetPosition(pos);
										itemList.push_back(objectItem[j]);
										break;
									case ID_TEX_WEAPON_REWARD:
										objectItem[j]->SetState(WEAPONREWARD_STATE_SHOW);
										objectItem[j]->SetPosition(pos);
										break;
									case ID_TEX_KATANA:
										objectItem[j]->SetState(KATANA_STATE_SHOW);
										objectItem[j]->SetPosition(pos);
										break;
									}
								}
							}
							objectCollision.erase(objectCollision.begin() + i);
						}
					}
				}
			}

			else if (isChangeLevel)
			{
				for (int i = 0; i < enemyList.size(); i++)
				{
					float l, t, r, b;
					enemyList[i]->GetBoundingBox(l, t, r, b);
					RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

					float L, T, R, B;
					whip->GetBoundingBox(L, T, R, B);
					RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

					bool result = whip->checkCollision(rect1, rect2);

					if (result)
					{
						enemyList[i]->SetState(ZOMBIE_STATE_DIE);
						enemyList.erase(enemyList.begin() + i);
					}
				}
				for (int i = 0; i < objectCollision.size(); i++)
				{
					float l, t, r, b;
					objectCollision[i]->GetBoundingBox(l, t, r, b);
					RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

					float L, T, R, B;
					whip->GetBoundingBox(L, T, R, B);
					RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

					bool result = whip->checkCollision(rect1, rect2);

					if (result)
					{
						D3DXVECTOR2 pos = objectCollision[i]->getPosition();
						objectCollision[i]->SetState(CANDLE_STATE_HIDE);

						std::string a = objectCollision[i]->getIdHiddenItem();

						for (int j = 0; j < objectItem.size(); j++)
						{
							std::string b = objectItem[j]->getIdHiddenItem();
							if (a.compare(b) == 0)
							{
								switch (objectItem[j]->getID())
								{
								case ID_TEX_HEART:
									objectItem[j]->SetState(HEART_STATE_SHOW);
									objectItem[j]->SetPosition(pos);
									itemList.push_back(objectItem[j]);
									break;
								case ID_TEX_SMALL_HEART:
									objectItem[j]->SetState(SMALL_HEART_STATE_SHOW);
									objectItem[j]->SetPosition(pos);
									break;
								case ID_TEX_MIRACULOUS_BAG:
									objectItem[j]->SetState(MIRACULOUSBAG_STATE_SHOW);
									objectItem[j]->SetPosition(pos);
									break;
								case ID_TEX_CROSS:
									objectItem[j]->SetState(CROSS_STATE_SHOW);
									objectItem[j]->SetPosition(pos);
									break;
								case ID_TEX_FIRE_BOMB:
									objectItem[j]->SetState(ID_TEX_FIRE_BOMB);
									objectItem[j]->SetPosition(pos);
									break;
								}
							}
						}
						objectCollision.erase(objectCollision.begin() + i);
					}
				}
				RemoveWhip();
				objectCollision.clear();
			}
		}
		else return;
	}

}

bool Simon::isOnGround()
{
	if (y >= GROUND_POSITION)
		return true;
	return false;
}

void Simon::handleState()
{
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_MOVE_SPEED;
		nx = 1;
		checkRewind = true;
		currentAnimation = SIMON_ANI_WALKING;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		checkRewind = true;
		currentAnimation = SIMON_ANI_WALKING;
		break;

	case SIMON_STATE_JUMPING:
		if (!jumped)
		{
			jumped = true;
			vy = -SIMON_JUMP_SPEED_Y;
			break;
		}

		if (vy < 0)
		{
			currentAnimation = SIMON_ANI_JUMPING;
		}
		else if (isOnGround() && jumped)
		{
			SetState(SIMON_STATE_IDLE);
			jumped = false;
		}
		checkRewind = false;
		break;

	case SIMON_STATE_ATTACK_JUMP:
		attacking = true;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_ATTACK_STAND:
		attacking = true;
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_SITDOWN:
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_SITDOWN;
		break;

	case SIMON_STATE_ATTACK_SITDOWN:
		attacking = true;
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_IDLE;
		break;

	case SIMON_STATE_CHANGECOLOR:
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_COLOR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_CHANGECOLOR1:
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_COLOR1;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_GO_UP_STAIR_RIGHT:
		nx = 1;
		checkRewind = false;
		vy = -SIMON_UP_STAIR_SPEED_Y;
		vx = SIMON_UP_STAIR_SPEED_X;
		currentAnimation = SIMON_ANI_GO_STAIR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_GO_DOWN_STAIR_RIGHT:
		nx = 1;
		checkRewind = false;
		vy = SIMON_UP_STAIR_SPEED_Y;
		vx = -SIMON_MOVE_SPEED;
		currentAnimation = SIMON_ANI_GO_STAIR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_GO_DOWN_STAIR_LEFT:
		nx = -1;
		checkRewind = false;
		vy = SIMON_UP_STAIR_SPEED_Y;
		vx = -SIMON_MOVE_SPEED;
		currentAnimation = SIMON_ANI_GO_STAIR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_IDLE_ON_STAIR:
		new_y = y;
		vy = 0;
		vx = 0;
		currentAnimation = SIMON_ANI_IDLE_STAIR;
		y = new_y;
		break;

	case SIMON_STATE_HURT:
		if (!jumped)
		{
			jumped = true;
			vy = -SIMON_JUMP_SPEED_Y;
			x -= sin(2.5*3.14 / 100) * 100;
			break;
		}
		if (vy < 0)
		{
			currentAnimation = SIMON_ANI_HURT;
		}
		else if (isOnGround() && jumped)
		{
			SetState(SIMON_STATE_IDLE);
			jumped = false;
		}
		checkRewind = false;
		break;
	}

	animations.find(currentAnimation)->second->SetLoop(checkRewind);
}

void Simon::Reset(int currentAnimation)
{
	if (currentAnimation == SIMON_ANI_GO_STAIR)
	{
		if (animations.find(currentAnimation)->second->IsFinished())
		{
			animations.find(currentAnimation)->second->SetFinish(false);
			SetState(SIMON_STATE_IDLE_ON_STAIR);
		}
	}
	if (animations.find(currentAnimation)->second->IsFinished())
	{
		attacking = false;
		animations.find(currentAnimation)->second->SetFinish(false);
		SetState(SIMON_STATE_IDLE);
	}
}

int Simon::IsAttacking()
{
	return isChangeLevel;
}

RECT Simon::getBoundingboxWhip()
{
	return whip->getBounding();
}

void Simon::RemoveWhip()
{
	if (whip != nullptr)
		delete whip;
}

Simon::~Simon()
{
	DirectInput* directInput = DirectInput::getInstance();
	RemoveWhip();
	__unhook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__unhook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__unhook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);
}
