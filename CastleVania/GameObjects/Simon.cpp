#include "Simon.h"
#include "BurnBarrel.h"
#include "../GameObjects/Heart.h"
#include "../GameObjects/WeaponReward.h"	
#include "../GameObjects/MiraculousBag.h"
#include "../GameObjects/Dagger.h"
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
#include "../DebugOut//DebugOut.h"

constexpr float SIMON_MOVE_SPEED = 0.1f;
constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.42f;
constexpr float SIMON_GRAVITY = 0.0012f;
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
	levelWhip = 1;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	whip = new Whip();
	baseInfo = new BaseInfo();
	SetPosition(D3DXVECTOR2(0, 0));
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	handleState();
	UpdateWeapon(dt, coObjects);
	SetupAtacking();

	if (level == 0)
	{
		if (GetTickCount() - comeEntranceStart <= SIMON_ENTRANCE_TIME)
			SetState(SIMON_STATE_WALKING_RIGHT);
		else if (comeEntranceStart > 0)
			comeEntranceStart = 0;
	}

	handleCollisionStair();

	handleCollisionObjectGame(dt, coObjects);
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

void Simon::OnKeyStateChange(BYTE * states)//state
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

void Simon::OnKeyDown(int KeyCode)//event
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	DirectInput* directInput = DirectInput::getInstance();

	switch (state)
	{
	case SIMON_STATE_IDLE:
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
	case SIMON_STATE_IDLE_ON_STAIR:
		if (KeyCode == DIK_X) SetState(SIMON_STATE_JUMPING);
		if (KeyCode == DIK_Z && !directInput->IsKeyDown(DIK_UP))
		{
			SetState(SIMON_STATE_ATTACK_STAND);
		}
		else if (directInput->IsKeyDown(DIK_UP) && KeyCode == DIK_Z)
		{
			enableSubWeapon = true;
			SetState(SIMON_STATE_ATTACK_STAND);
		}
		break;
	case SIMON_STATE_JUMPING:
		if (KeyCode == DIK_Z && !directInput->IsKeyDown(DIK_UP))
		{
			SetState(SIMON_STATE_ATTACK_JUMP);
		}
		else if (directInput->IsKeyDown(DIK_UP) && KeyCode == DIK_Z)
		{
			enableSubWeapon = true;
			SetState(SIMON_STATE_ATTACK_JUMP);
		}
		else if (KeyCode == DIK_J)
		{
			SetState(SIMON_STATE_IDLE);
		}
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_Z && !directInput->IsKeyDown(DIK_UP))
		{
			SetState(SIMON_STATE_ATTACK_SITDOWN);
		}
		else if (directInput->IsKeyDown(DIK_UP) && KeyCode == DIK_Z)
		{
			enableSubWeapon = true;
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

void Simon::SetSubWeapon(EntityID IdItemSubWeapon)
{
	switch (IdItemSubWeapon)
	{
	case ID_TEX_DAGGER:
		baseInfo->setIdSubWeapon(IdItemSubWeapon);
		baseInfo->setSubWeapon(new DaggerWeapon());
		break;
	default:
		break;
	}
}

void Simon::SetupAtacking()
{
	if (attacking && !enableSubWeapon)
	{
		whip->SetPosition(D3DXVECTOR2(x, y));
		if (levelWhip == 1)
		{
			whip->SetState(WHIT_STATE_1);
		}
		else if (levelWhip == 2)
		{
			whip->SetState(WHIT_STATE_2);
		}
		else if (levelWhip == 3)
		{
			whip->SetState(WHIT_STATE_3);
		}
	}
	else if (attacking && enableSubWeapon && baseInfo->getHeart() > 0 && baseInfo->getSubWeapon())
	{
		baseInfo->getSubWeapon()->SetPosition(D3DXVECTOR2(x, y));
		baseInfo->getSubWeapon()->setDirection(nx);
		enableSubWeapon = false;
	}
}

void Simon::RenderWeapon(LPANIMATION animation, Viewport * viewport)
{
	if (attacking)
	{
		whip->updatePostision(animation->getCurrentFrame(), currentAnimation, nx);
		whip->draw(nx, viewport);
		if (whip->getframe() == 2) whip->animations.find(currentAnimation)->second->SetFinish(true);
	}
	if (baseInfo->getSubWeapon())
	{
		baseInfo->getSubWeapon()->Render(viewport);
	}
}

void Simon::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (attacking)
	{
		whip->Update(dt, coObjects);
	}

	if (baseInfo->getHeart() == 0) {
		baseInfo->setIdSubWeapon(ID_TEX_NULL);
	}

	if (baseInfo->getSubWeapon())
	{
		baseInfo->getSubWeapon()->Update(dt, coObjects);
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 25;
	top = y;
	right = x + width + 10;
	bottom = y + height;
}

void Simon::Render(Viewport* viewport)
{
	//RenderBoundingBox(viewport);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	LPANIMATION animation = animations.find(currentAnimation)->second;

	if (animation != nullptr)
	{
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;
		animation->Render(pos.x, pos.y, flip);
	}

	RenderWeapon(animation, viewport);
}

bool Simon::isOnGround()
{
	if (vy == 0)
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
		if (!isjumping && isOnGround())
		{
			isjumping = true;
			vy = -SIMON_JUMP_SPEED_Y;
			break;
		}
		if (vy < 0) {
			currentAnimation = SIMON_ANI_JUMPING;
		}
		else if (isOnGround() && isjumping)
		{
			isjumping = false;
			SetState(SIMON_STATE_IDLE);
		}
		checkRewind = true;
		break;

	case SIMON_STATE_ATTACK_JUMP:
		attacking = true;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_ATTACK_STAND:
		vx = 0;
		attacking = true;
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
		if (!isjumping)
		{
			isjumping = true;
			vy = -SIMON_JUMP_SPEED_Y;
			x -= sin(2.5*3.14 / 100) * 100;
			break;
		}
		if (vy < 0)
		{
			currentAnimation = SIMON_ANI_HURT;
		}
		else if (isOnGround() && isjumping)
		{
			SetState(SIMON_STATE_IDLE);
		}
		checkRewind = false;
		break;
	}
	DebugOut(L"state:{%d}\n", state);
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
		SetState(SIMON_STATE_IDLE);
		attacking = false;
		animations.find(currentAnimation)->second->SetFinish(false);
	}
}

void Simon::handleCollisionStair()
{
	DirectInput* directInput = DirectInput::getInstance();
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
}

void Simon::handleCollisionObjectGame(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
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
				Dx = min_tx * dx + nx * 0.11f;
				if (nx != 0) vx = 0;
				break;
			case ID_TEX_ENTRANCE:
				comeEntranceStart = GetTickCount();
				break;
			case ID_TEX_WALL_ENTRANCE:
				level = true;
				x = 50;
				SetState(SIMON_STATE_IDLE);
				break;
			case ID_TEX_WEAPON_REWARD:
				SetState(SIMON_STATE_CHANGECOLOR);
				if (levelWhip == 1)
				{
					levelWhip = 2;
				}
				else if (levelWhip == 2)
				{
					levelWhip = 3;
				}
				coEvents[i]->obj->SetState(STATE_DETROY);
				break;
			case ID_TEX_HEART:
				baseInfo->setHeart(baseInfo->getHeart() + 10);
				coEvents[i]->obj->SetState(STATE_DETROY);
				break;
			case ID_TEX_DAGGER:
				SetSubWeapon(ID_TEX_DAGGER);
				
				coEvents[i]->obj->SetState(STATE_DETROY);
				break;
			case ID_TEX_MIRACULOUS_BAG:
			case ID_TEX_SMALL_HEART:
				baseInfo->setHeart(baseInfo->getHeart() + 1);
				coEvents[i]->obj->SetState(STATE_DETROY);
				break;
			case ID_TEX_PODIUM_ON_WALL:
			case ID_TEX_FLOOR:
				Dy = min_ty * dy + ny * 0.1f;
				if (ny != 0) vy = 0;
				break;
			}
		}
		x += Dx;
		y += Dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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

