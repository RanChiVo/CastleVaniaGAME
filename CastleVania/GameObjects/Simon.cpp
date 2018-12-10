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
#include "../Brick.h"
#include "../GameObjects/Entrance.h"
#include "../EntityID.h"
#include "../Flip.h"

constexpr float SIMON_MOVE_SPEED = 0.1f;
constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.42f;
constexpr float SIMON_GRAVITY = 0.0009f;
constexpr int SIMON_PROTECT_TIME = 2000;
constexpr float SIMON_UP_STAIR_SPEED = 0.09f;

constexpr auto GROUND_POSITION = 293;
constexpr auto MAPSIZE_WIDTH = 1475;
constexpr auto P0SITION_ENTRANCE = 1300;

constexpr int SIMON_UNTOUCHABLE_TIME = 5000;
constexpr int SIMON_ENTRANCE_TIME = 3000;

Simon::Simon()
{	
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);

	SetPosition(D3DXVECTOR2(1200, 250));

	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	WHIP_STATE = 1;
	isChangeLevel = true;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);
	handleState();

	if (GetTickCount() - comeEntranceStart < SIMON_ENTRANCE_TIME)
		SetState(SIMON_STATE_WALKING_RIGHT);
	else if (comeEntranceStart > 0)
		comeEntranceStart = 0;
	
	
	vy += SIMON_GRAVITY*dt ;


	for (int i = 0; i < coObjects->size(); i++)
	{
		switch (coObjects->at(i)->getID())
		{
		case ID_COLLISION_STAIR:

			float l, t, r, b;
			coObjects->at(i)->GetBoundingBox(l, t, r, b);
			RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

			float L, T, R, B;
			GetBoundingBox(L, T, R, B);
			RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

			bool result = checkCollision(rect1, rect2);

			if (result)
			{
				if (state != SIMON_STATE_GO_UP_STAIR_RIGHT)
				{
					if (DirectInput::getInstance()->IsKeyDown(DIK_UP))
					{
						SetState(SIMON_STATE_GO_UP_STAIR_RIGHT);
					}

					else if (DirectInput::getInstance()->IsKeyDown(DIK_DOWN))
					{
						SetState(SIMON_STATE_GO_DOWN_STAIR_LEFT);
					}
				}
				else if (state == SIMON_STATE_GO_UP_STAIR_RIGHT)
				{
					SetState(SIMON_STATE_IDLE);

					if (DirectInput::getInstance()->IsKeyUp(DIK_UP))
					{
						SetState(SIMON_STATE_IDLE_UP_STAIR_RIGHT);
					}
				}
			}
			break;
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
				x = 800;
				break;
			case ID_TEX_HEART:
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_HEART)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
					}
				}
				SetState(SIMON_STATE_CHANGECOLOR);
				break;
			case ID_TEX_WEAPON_REWARD:
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_WEAPON_REWARD)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
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
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_KATANA)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
					}
				}
				break;
			case ID_TEX_MIRACULOUS_BAG:
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_MIRACULOUS_BAG)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
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
			default:
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

	
	if (objectList.size() < 10 && !isChangeLevel)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_TEX_HEART:
			case ID_TEX_WEAPON_REWARD:
			case ID_TEX_KATANA:
			case ID_TEX_BURNBARREL:
				objectList.push_back(coObjects->at(i));
				break;
			}
		}
	}
	else if (objectList.size() < 60 && isChangeLevel)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_TEX_CANDLE:
			case ID_TEX_HEART:
			case ID_TEX_WEAPON_REWARD:
			case ID_TEX_SMALL_HEART:
			case ID_TEX_CROSS:
			case ID_TEX_FIRE_BOMB:
				objectList.push_back(coObjects->at(i));
				break;
			}
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
		if (KeyCode == DIK_X && isOnGround())
			SetState(SIMON_STATE_JUMPING);
		else if (KeyCode == DIK_Z || directInput->IsKeyDown(DIK_J) && KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_STAND);
		}
		break;
		if (KeyCode == DIK_UP )

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
	bottom = y + height - 10;
}

void Simon::Render(Viewport* viewport)
{
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
				for (int i = 0; i < objectList.size() - 5; i++)
				{
					float l, t, r, b;
					objectList[i]->GetBoundingBox(l, t, r, b);
					RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

					float L, T, R, B;
					whip->GetBoundingBox(L, T, R, B);
					RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

					bool result = whip->checkCollision(rect1, rect2);

					if (result)
					{
						D3DXVECTOR2 pos = objectList[i]->getPosition();
						objectList[i]->SetPosition(D3DXVECTOR2(-100, -100));

						switch (i)
						{
						case 0:
							objectList[5]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[5]->SetState(HEART_STATE_SHOW);
							break;
						case 1:
							objectList[6]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[6]->SetState(WEAPONREWARD_STATE_SHOW);
							break;
						case 2:
							objectList[7]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[7]->SetState(HEART_STATE_SHOW);
							break;
						case 3:
							objectList[8]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[8]->SetState(WEAPONREWARD_STATE_SHOW);
							break;
						case 4:
							objectList[9]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[9]->SetState(KATANA_STATE_SHOW);
							itemList.push_back(objectList[9]);
							break;
						}
					}
				}
			}

			else if (isChangeLevel)
			{
				for (int i = 0; i < objectList.size(); i++)
				{
					float l, t, r, b;					objectList[i]->GetBoundingBox(l, t, r, b);
					RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };

					float L, T, R, B;
					whip->GetBoundingBox(L, T, R, B);
					RECT rect2 = RECT{ int(L), int(T), int(R), int(B) };

					bool result = whip->checkCollision(rect1, rect2);

					if (result)
					{
						D3DXVECTOR2 pos = objectList[i]->getPosition();
						objectList[i]->SetPosition(D3DXVECTOR2(-100, -100));
						switch (i)
						{
						case 0:
							objectList[5]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[5]->SetState(HEART_STATE_SHOW);
							break;
						case 1:
							objectList[6]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[6]->SetState(WEAPONREWARD_STATE_SHOW);
							break;
						case 2:
							objectList[7]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[7]->SetState(HEART_STATE_SHOW);
							break;
						case 3:
							objectList[8]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[8]->SetState(WEAPONREWARD_STATE_SHOW);
							break;
						case 4:
							objectList[9]->SetPosition(D3DXVECTOR2(pos.x, pos.y + 15));
							objectList[9]->SetState(KATANA_STATE_SHOW);
							itemList.push_back(objectList[9]);
							break;
						}
					}

				}
				RemoveWhip();
				objectList.clear();
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

	case SIMON_STATE_GO_UP_STAIR:
		checkRewind = true;
		vy = -SIMON_UP_STAIR_SPEED;
		vx = SIMON_MOVE_SPEED;
		currentAnimation = SIMON_ANI_GO_STAIR;
		checkUp = true;
		break;

	case SIMON_STATE_GO_DOWN_STAIR:
		checkRewind = true;
		vy = SIMON_UP_STAIR_SPEED;
		vx =-SIMON_MOVE_SPEED;
		currentAnimation = SIMON_ANI_GO_STAIR;
		checkUp = false;
		break;

	case SIMON_STATE_IDLE_UP_STAIR:
		currentAnimation = SIMON_ANI_IDLE_STAIR;
		vx = 0;
		checkUp = true;
		break;

	case SIMON_STATE_IDLE_DOWN_STAIR:
		currentAnimation = SIMON_ANI_IDLE_STAIR;
		vx = 0;
		checkUp = false;
		break;
	}
	
	animations.find(currentAnimation)->second->SetLoop(checkRewind);
}

void Simon::Reset(int currentAnimation)
{
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
