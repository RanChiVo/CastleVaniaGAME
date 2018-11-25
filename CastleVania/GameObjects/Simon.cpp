#include "Simon.h"
#include "BurnBarrel.h"
#include "../GameObjects/Heart.h"
#include "../GameObjects/WeaponReward.h"	
#include "../GameObjects/MiraculousBag.h"
#include "../Brick.h"
#include "../EntityID.h"


constexpr auto GROUND_POSITION = 294;
constexpr auto MAPSIZE_WIDTH = 1475;

Simon::Simon()
{
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);

	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE_RIGHT;
	WHIP_STATE = 1;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	handleState();

	if (objectList.size() == 0 && objectList.size() != coObjects->size())
	{
		for (int i = 1; i < coObjects->size() - 5; i++)
		{
			objectList.push_back(coObjects->at(i));
		}
	}

	vy += SIMON_GRAVITY * dt;

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
			case ID_TEX_BRICK:
				Dx = min_tx * dx + nx * 0.4f;
				if (nx != 0) vx = 0;
				break;
			case ID_TEX_HEART:
				if (nx != 0) vx = 0;
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_HEART)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
					}
				}
				break;
			case ID_TEX_WEAPON_REWARD:
				if (nx != 0) vx = 0;
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_WEAPON_REWARD)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
					}
				}
				if (level == 1)
				{
					level = 2;
					SetState(SIMON_STATE_CHANGECOLOR);
				}
				else if (level == 2)
				{
					level = 3;
					SetState(SIMON_STATE_CHANGECOLOR1);
				}
				break;
			case ID_TEX_KATANA:
				if (nx != 0) vx = 0;
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

					if (coObjects->at(i)->getID() == ID_TEX_ENTRANCE)
					{
						D3DXVECTOR2 pos = coObjects->at(i)->getNewPos();
						coObjects->at(i)->SetPosition(pos);
				}
					}
				break;
			case ID_TEX_FLOOR:
				Dy = min_ty * dy + ny * 0.4f;
				if (ny != 0) vy = 0;
				if (x >= 1430)
				{
					for (int i = 0; i < coObjects->size(); i++)
					{
						if (coObjects->at(i)->getID() == ID_TEX_MIRACULOUS_BAG)
						{
							coObjects->at(i)->SetState(MIRACULOUSBAG_STATE_SHOW);
							coObjects->at(i)->SetPosition(D3DXVECTOR2(1279, 330));
						}
					}
				}
				break;

			case ID_TEX_ENTRANCE:
				if (nx != 0) vx = 0;
				//Dx = min_tx * dx + nx * 0.4f ;
				SetState(SIMON_STATE_WALKING_RIGHT);

				break;
			case ID_TEX_BURNBARREL:
				break;
			}
		}
		x += Dx;
		y += Dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::loadResource()
{
	LPANIMATION ani;
	//idle right

	ani = new Animation(100);
	ani->Add("WalkingRight4");
	Animations::GetInstance()->Add(SIMON_ANI_IDLE_RIGHT, ani);

	//idle left
	ani = new Animation(100);
	ani->Add("WalkingLeft4");
	Animations::GetInstance()->Add(SIMON_ANI_IDLE_LEFT, ani);

	// walk right
	ani = new Animation(100);
	ani->Add("WalkingRight1");
	ani->Add("WalkingRight2");
	ani->Add("WalkingRight3");
	ani->Add("WalkingRight4");
	Animations::GetInstance()->Add(SIMON_ANI_WALKING_RIGHT, ani);

	// walk left
	ani = new Animation(100);
	ani->Add("WalkingLeft1");
	ani->Add("WalkingLeft2");
	ani->Add("WalkingLeft3");
	ani->Add("WalkingLeft4");
	Animations::GetInstance()->Add(SIMON_ANI_WALKING_LEFT, ani);

	//jump right
	ani = new Animation(100);
	ani->Add("JumpRight");
	Animations::GetInstance()->Add(SIMON_ANI_JUMPING_RIGHT, ani);

	//jump left
	ani = new Animation(100);
	ani->Add("JumpLeft");
	Animations::GetInstance()->Add(SIMON_ANI_JUMPING_LEFT, ani);

	//sit down right
	ani = new Animation(100);
	ani->Add("SitdownRight");
	Animations::GetInstance()->Add(SIMON_ANI_SITDOWN_RIGHT, ani);

	//sit down left
	ani = new Animation(100);
	ani->Add("SitdownLeft");
	Animations::GetInstance()->Add(SIMON_ANI_SITDOWN_LEFT, ani);

	//attack standing right
	ani = new Animation(200);	//ani->Add("AttackStandRight1");
	ani->Add("AttackStandRight1");
	ani->Add("AttackStandRight2");
	ani->Add("AttackStandRight3");
	Animations::GetInstance()->Add(SIMON_ANI_ATTACK_STANDING_RIGHT, ani);

	//attack standing left
	ani = new Animation(200);
	ani->Add("AttackStandLeft1");
	ani->Add("AttackStandLeft2");
	ani->Add("AttackStandLeft3");
	Animations::GetInstance()->Add(SIMON_ANI_ATTACK_STANDING_LEFT, ani);

	//attack Sitdown right
	ani = new Animation(200);
	ani->Add("AttackSitdownRight1");
	ani->Add("AttackSitdownRight2");
	ani->Add("AttackSitdownRight3");
	Animations::GetInstance()->Add(SIMON_ANI_ATTACK_SITDOWN_RIGHT, ani);

	//attack Sitdown Left
	ani = new Animation(200);
	ani->Add("AttackSitdownLeft1");
	ani->Add("AttackSitdownLeft2");
	ani->Add("AttackSitdownLeft3");

	Animations::GetInstance()->Add(SIMON_ANI_ATTACK_SITDOWN_LEFT, ani);

	ani = new Animation(100);
	ani->Add("ChangeColorRight1");
	ani->Add("ChangeColorRight2");
	ani->Add("ChangeColorRight3");
	ani->Add("ChangeColorRight4");
	ani->Add("ChangeColorRight5");
	ani->Add("ChangeColorRight6");

	Animations::GetInstance()->Add(SIMON_ANI_COLOR_RIGHT, ani);

	ani = new Animation(100);
	ani->Add("ChangeColorLeft1");
	ani->Add("ChangeColorLeft2");
	ani->Add("ChangeColorLeft3");
	ani->Add("ChangeColorLeft4");
	ani->Add("ChangeColorLeft5");
	ani->Add("ChangeColorLeft6");

	Animations::GetInstance()->Add(SIMON_ANI_COLOR_LEFT, ani);


	ani = new Animation(100);
	ani->Add("1ChangeColorRight1");
	ani->Add("1ChangeColorRight2");
	ani->Add("1ChangeColorRight3");
	ani->Add("1ChangeColorRight4");
	ani->Add("1ChangeColorRight5");
	ani->Add("1ChangeColorRight6");

	Animations::GetInstance()->Add(SIMON_ANI_COLOR_RIGHT1, ani);

	ani = new Animation(100);
	ani->Add("1ChangeColorLeft1");
	ani->Add("1ChangeColorLeft2");
	ani->Add("1ChangeColorLeft3");
	ani->Add("1ChangeColorLeft4");
	ani->Add("1ChangeColorLeft5");
	ani->Add("1ChangeColorLeft6");

	Animations::GetInstance()->Add(SIMON_ANI_COLOR_LEFT1, ani);


	AddAnimation(SIMON_ANI_IDLE_LEFT);		// idle right
	AddAnimation(SIMON_ANI_IDLE_RIGHT);		// idle left
	AddAnimation(SIMON_ANI_WALKING_LEFT);		// walk right
	AddAnimation(SIMON_ANI_WALKING_RIGHT);		// walk left

	AddAnimation(SIMON_ANI_JUMPING_RIGHT);		//jump right
	AddAnimation(SIMON_ANI_JUMPING_LEFT);		//jump left

	AddAnimation(SIMON_ANI_SITDOWN_RIGHT);		//sitdown right
	AddAnimation(SIMON_ANI_SITDOWN_LEFT);		//sitdown left

	AddAnimation(SIMON_ANI_ATTACK_STANDING_RIGHT);		//attack standing right
	AddAnimation(SIMON_ANI_ATTACK_STANDING_LEFT);		//attack standing left
	AddAnimation(SIMON_ANI_ATTACK_SITDOWN_RIGHT);		//attack sitdown left
	AddAnimation(SIMON_ANI_ATTACK_SITDOWN_LEFT);		//attack sitdown right

	AddAnimation(SIMON_ANI_COLOR_RIGHT);
	AddAnimation(SIMON_ANI_COLOR_LEFT);


	AddAnimation(SIMON_ANI_COLOR_RIGHT1);
	AddAnimation(SIMON_ANI_COLOR_LEFT1);


	SetPosition(D3DXVECTOR2(50.0f, 0));
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
		if (directInput->IsKeyDown(DIK_K) && isOnGround())
		{
			SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else if (directInput->IsKeyDown(DIK_H) && isOnGround())
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
		if (KeyCode == DIK_X)
			SetState(SIMON_STATE_JUMPING);
		else if (KeyCode == DIK_Z || directInput->IsKeyDown(DIK_J) && KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_STAND);
		}
		break;
	case SIMON_STATE_JUMPING:
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

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_SIMON)->Get("WalkingRight1")->getRect();
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
		animation->Render(pos.x, pos.y);
		
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
			whip->updatePostision(animation->getCurrentFrame(), currentAnimation);
			whip->draw(nx, viewport);
			if (whip->getframe() == 2) whip->animations.find(currentAnimation)->second->SetFinish(true);

			for (int i = 0; i < objectList.size() - 6; i++)
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
					objectList[i]->SetPosition(D3DXVECTOR2(0, -200));
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

	
	}
	else return;
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
		currentAnimation = SIMON_ANI_WALKING_RIGHT;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		checkRewind = true;
		currentAnimation = SIMON_ANI_WALKING_LEFT;
		break;

	case SIMON_STATE_JUMPING:
		if (!jumped)
		{
			jumped = true;
			vy = -SIMON_JUMP_SPEED_Y;
			break;
		}

		if (vy < 0 )
		{
			if (nx == 1) currentAnimation = SIMON_ANI_JUMPING_RIGHT;
			else currentAnimation = SIMON_ANI_JUMPING_LEFT;
		}
		else
		{
			if (nx == 1) currentAnimation = SIMON_ANI_IDLE_RIGHT;
			else currentAnimation = SIMON_ANI_IDLE_LEFT;
		}

		if (isOnGround() && jumped)
		{
			SetState(SIMON_STATE_IDLE);
			jumped = false;
		}
		checkRewind = false;
		break;
	case SIMON_STATE_ATTACK_JUMP:
	case SIMON_STATE_ATTACK_STAND:
		attacking = true;
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_ATTACK_STANDING_RIGHT;
		else currentAnimation = SIMON_ANI_ATTACK_STANDING_LEFT;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_SITDOWN:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_SITDOWN_RIGHT;
		else currentAnimation = SIMON_ANI_SITDOWN_LEFT;
		break;

	case SIMON_STATE_ATTACK_SITDOWN:
		attacking = true;
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_ATTACK_SITDOWN_RIGHT;
		else currentAnimation = SIMON_ANI_ATTACK_SITDOWN_LEFT;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_IDLE_RIGHT;
		else currentAnimation = SIMON_ANI_IDLE_LEFT;
		break;

	case SIMON_STATE_CHANGECOLOR:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_COLOR_RIGHT;
		else currentAnimation = SIMON_ANI_COLOR_LEFT;
		Reset(currentAnimation);
		break;
	case SIMON_STATE_CHANGECOLOR1:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_COLOR_RIGHT1;
		else currentAnimation = SIMON_ANI_COLOR_LEFT1;
		Reset(currentAnimation);
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
	return attacking;
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
