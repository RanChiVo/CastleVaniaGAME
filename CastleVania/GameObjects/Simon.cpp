#include "Simon.h"
#include "BurnBarrel.h"
#include "../GameObjects/Heart.h"
#include "../GameObjects/WeaponReward.h"	
#include "../GameObjects/MiraculousBag.h"
#include "../Brick.h"
#include "../EntityID.h"
#include "../Flip.h"

constexpr auto GROUND_POSITION = 293;
constexpr auto MAPSIZE_WIDTH = 1475;

Simon::Simon()
{
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);

	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	WHIP_STATE = 1;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	handleState();

	if (objectList.size() == 0 && objectList.size() != coObjects->size())
	{
		for (int i = 1; i < coObjects->size() - 4; i++)
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
			//	Dx = min_tx * dx + nx * 0.4f;
				isChangeLevel = true;
	
				break;

			case ID_TEX_HEART:
				if (ny != 0) vy = 0;
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_HEART)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
					}
				}
				break;

			case ID_TEX_WEAPON_REWARD:
				if (ny != 0) vy = 0;
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
				if (ny != 0) vy = 0;
				for (int i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->getID() == ID_TEX_KATANA)
					{
						coObjects->at(i)->SetPosition(D3DXVECTOR2(-100, -100));
					}
				}
				break;

			case ID_TEX_MIRACULOUS_BAG:
				if (ny != 0) vy = 0;
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
				Dx = min_tx * dx + nx * 0.4f ;
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
	ani->Add("Walking4");
	Animations::GetInstance()->Add(SIMON_ANI_IDLE, ani);

	// walk right
	ani = new Animation(100);
	ani->Add("Walking1");
	ani->Add("Walking2");
	ani->Add("Walking3");
	ani->Add("Walking4");
	Animations::GetInstance()->Add(SIMON_ANI_WALKING, ani);

	//jump right
	ani = new Animation(100);
	ani->Add("Jump");
	Animations::GetInstance()->Add(SIMON_ANI_JUMPING, ani);

	//sit down right
	ani = new Animation(100);
	ani->Add("Sitdown");
	Animations::GetInstance()->Add(SIMON_ANI_SITDOWN, ani);

	//attack standing right
	ani = new Animation(200);	//ani->Add("AttackStandRight1");
	ani->Add("AttackStand1");
	ani->Add("AttackStand2");
	ani->Add("AttackStand3");
	Animations::GetInstance()->Add(SIMON_ANI_ATTACK_STANDING, ani);

	//attack Sitdown right
	ani = new Animation(200);
	ani->Add("AttackSitdown1");
	ani->Add("AttackSitdown2");
	ani->Add("AttackSitdown3");
	Animations::GetInstance()->Add(SIMON_ANI_ATTACK_SITDOWN, ani);

	ani = new Animation(100);
	ani->Add("1ChangeColor1");
	ani->Add("1ChangeColor2");
	ani->Add("1ChangeColor3");
	
	Animations::GetInstance()->Add(SIMON_ANI_COLOR, ani);

	ani = new Animation(100);
	ani->Add("2ChangeColor1");
	ani->Add("2ChangeColor2");
	ani->Add("2ChangeColor3");

	Animations::GetInstance()->Add(SIMON_ANI_COLOR1, ani);

	AddAnimation(SIMON_ANI_IDLE);		// idle left
	AddAnimation(SIMON_ANI_WALKING);		// walk left
	AddAnimation(SIMON_ANI_JUMPING);		//jump right
	AddAnimation(SIMON_ANI_SITDOWN);		//sitdown right
	AddAnimation(SIMON_ANI_ATTACK_STANDING);		//attack standing right
	AddAnimation(SIMON_ANI_ATTACK_SITDOWN);		//attack sitdown left
	AddAnimation(SIMON_ANI_COLOR);
	AddAnimation(SIMON_ANI_COLOR1);

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
		if (directInput->IsKeyDown(DIK_K) )
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
		if (KeyCode == DIK_X && isOnGround() )
			SetState(SIMON_STATE_JUMPING);
		else if (KeyCode == DIK_Z || directInput->IsKeyDown(DIK_J) && KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_STAND);
		}
		break;
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
	if (state == SIMON_STATE_JUMPING)
	{
		if (isOnGround() && jumped)
		{
			SetState(SIMON_STATE_IDLE);
		}
	}
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
			RemoveWhip();
			objectList.clear();
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
			currentAnimation = SIMON_ANI_JUMPING;
		}
		checkRewind = false;
		break;
	case SIMON_STATE_ATTACK_JUMP:
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
		jumped = false;
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
