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
#include "../Panther.h"
#include "../Door.h"
#include "../Viewport.h"
#include "../WaterEffect.h"
#include "../DarkBat.h"

constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.42f;
constexpr float SIMON_MOVE_SPEED = 0.12f;
constexpr float SIMON_GRAVITY = 0.001f;
constexpr float SIMON_HURT_SPEED_Y = 0.2f;
constexpr float SIMON_STAIR_SPEED = 0.06f;
constexpr DWORD SIMON_ENTRANCE_TIME = 1000;
constexpr DWORD INVISIBLE_TIME = 4000;
constexpr DWORD SIMON_UNTOUCHABLE_TIME = 2000;
constexpr DWORD SIMON_PROTECT_TIME = 2000;
constexpr DWORD SIMON_HURT_TIME = 1000;

Simon* Simon::_instance = nullptr;

Simon * Simon::getInstance()
{
	if (_instance == nullptr)
		_instance = new Simon();
	return _instance;
}

Simon::Simon()
{
	DirectInput* directInput = DirectInput::getInstance();
	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);
	id = ID_ENTITY_SIMON;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	WHIP_STATE = 1;
	levelWhip = 1;
	whip = new Whip();
	whip->SetPosition(getPosition());
	baseInfo = new BaseInfo();
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	UpdateWeapon(dt, coObjects);
	SetupAtacking();
	SetupSubWeapon(coObjects);
	handleState();
	
	if (GetTickCount() - comeEntranceStart <= SIMON_ENTRANCE_TIME)
		SetState(SIMON_STATE_WALKING_RIGHT);

	else if (comeEntranceStart > 0)
		comeEntranceStart = 0;

	updateCollisionStair();
	updateCollisionSubStair();
	handleCollisionObjectGame(dt, coObjects);

	if (startHurt > 0 && GetTickCount() - startHurt > SIMON_HURT_TIME)
	{
		startHurt = 0;
	}

	if (invisible_Potion_Start > 0 && GetTickCount() - invisible_Potion_Start > INVISIBLE_TIME)
	{
		invisible_Potion_Start = 0;
		isVisible = false;
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
	AddAnimation(SIMON_ANI_GO_UP_STAIR);
	AddAnimation(SIMON_ANI_GO_DOWN_STAIR);
	AddAnimation(SIMON_ANI_IDLE_GO_UP_STAIR);
	AddAnimation(SIMON_ANI_IDLE_GO_DOWN_STAIR);
	AddAnimation(SIMON_ANI_ATTACK_UP_STAIR);
	AddAnimation(SIMON_ANI_ATTACK_DOWN_STAIR);
	AddAnimation(SIMON_ANI_HURT);
}

void Simon::SetState(int state)
{
	this->state = state;
}

void Simon::OnKeyStateChange(BYTE * states)//state
{
	if (isMovingDoor)
	{
		return;
	}

	DirectInput* directInput = DirectInput::getInstance();

	switch (state)
	{
	case SIMON_STATE_IDLE:
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (directInput->IsKeyDown(DIK_RIGHT))
		{
			SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else if (directInput->IsKeyDown(DIK_LEFT))
		{
			SetState(SIMON_STATE_WALKING_LEFT);
		}
		else if (directInput->IsKeyDown(DIK_J) && isOnGround())
		{
			SetState(SIMON_STATE_SITDOWN);
		}
		if (originalStair)
		{
			if (directInput->IsKeyDown(DIK_UP))
			{
				if (originalStair->get_ny() > 0)
				{
					if (!isOnStair)
					{
						SetPosition(D3DXVECTOR2(originalStair->getPosition().x - 30, y));
					}
					SetState(SIMON_STATE_GO_UP_STAIR);
					updateCollisionStair();
				}
			}
			else if (directInput->IsKeyDown(DIK_DOWN))
			{
				if (originalStair->get_ny() < 0)
				{
					if (!isOnStair)
					{
						SetPosition(D3DXVECTOR2(originalStair->getPosition().x-15, y));
					}
					SetState(SIMON_STATE_GO_DOWN_STAIR);
					updateCollisionStair();
				}
			}
		}
		break;
	case SIMON_STATE_HURT:
		if (originalStair)
		{
			if (directInput->IsKeyDown(DIK_UP))
			{
				if (originalStair->get_ny() > 0)
				{
					if (!isOnStair)
					{
						SetPosition(D3DXVECTOR2(originalStair->getPosition().x - 30, y));
					}
					SetState(SIMON_STATE_GO_UP_STAIR);
					updateCollisionStair();
				}
			}
			else if (directInput->IsKeyDown(DIK_DOWN))
			{
				if (originalStair->get_ny() < 0)
				{
					if (!isOnStair)
					{
						SetPosition(D3DXVECTOR2(originalStair->getPosition().x - 15, y));
					}
					SetState(SIMON_STATE_GO_DOWN_STAIR);
					updateCollisionStair();
				}
			}
		}
		break;
	case SIMON_STATE_IDLE_UP_STAIR:
		if (originalStair)
		{
			if (isOnStair)
			{
				if (directInput->IsKeyDown(DIK_UP))
				{
					SetState(SIMON_STATE_GO_UP_STAIR);
				}
				else if (directInput->IsKeyDown(DIK_DOWN))
				{
					SetState(SIMON_STATE_GO_DOWN_STAIR);
				}
				else if (directInput->IsKeyDown(DIK_Z))
				{
					SetState(SIMON_STATE_ATTACK_UP_STAIR);
				}
			}
		}
		break;
	case SIMON_STATE_IDLE_DOWN_STAIR:
		if (originalStair)
		{
			if (isOnStair)
			{
				if (directInput->IsKeyDown(DIK_UP))
				{
					SetState(SIMON_STATE_GO_UP_STAIR);
				}
				else if (directInput->IsKeyDown(DIK_DOWN))
				{
					SetState(SIMON_STATE_GO_DOWN_STAIR);
					
				}
				else if (directInput->IsKeyDown(DIK_Z))
				{
					SetState(SIMON_STATE_ATTACK_DOWN_STAIR);
				}
			}
		}
		break;
	}
}

void Simon::OnKeyDown(int KeyCode)//event
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	DirectInput* directInput = DirectInput::getInstance();

	switch (KeyCode)
	{
	case DIK_A:
		SetPosition(D3DXVECTOR2(64.0f, 248.0f));
		Direct3DManager::getInstance()->getViewport()
			->SetPosition(Direct3DManager::getInstance()->getViewport()->getX(), 0);
		isInTunel = false;
		break;
	case DIK_B:
		SetPosition(D3DXVECTOR2(2867.45f, 60.58f));
		Direct3DManager::getInstance()
			->getViewport()->SetPosition(Direct3DManager::getInstance()->getViewport()->getX(), 0);
		isInTunel = false;
		break;
	case DIK_C:
		SetPosition(D3DXVECTOR2(5048.66f, 248.0f));
		isInTunel = true;
		Direct3DManager::getInstance()->getViewport()
			->SetPosition(Direct3DManager::getInstance()->getViewport()->getX(), 430);
		break;
	}

	if (isMovingDoor)
	{
		return;
	}
	switch (state)
	{
	case SIMON_STATE_IDLE:
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (KeyCode == DIK_X) SetState(SIMON_STATE_JUMPING);
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_STAND);
			if (directInput->IsKeyDown(DIK_UP))
			{
				SetState(SIMON_STATE_ATTACK_STAND_SUBWEAPON);
			}
		}
		break;
	case SIMON_STATE_JUMPING:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_JUMP);
			if (directInput->IsKeyDown(DIK_UP))
			{
				SetState(SIMON_STATE_ATTACK_JUMP_SUBWEAPON);
			}
		}
		else if (KeyCode == DIK_J)
		{
			SetState(SIMON_STATE_IDLE);
		}
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_SITDOWN);
			if (directInput->IsKeyDown(DIK_UP))
			{
				SetState(SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON);
			}
		}
		break;
	}
}

void Simon::OnKeyUp(int KeyCode)
{
	if (isMovingDoor)
	{
		return;
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		if (KeyCode == DIK_RIGHT)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (KeyCode == DIK_LEFT)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_SITDOWN:
	case SIMON_STATE_ATTACK_SITDOWN:
	case SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON:
		if (KeyCode == DIK_J)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_GO_UP_STAIR:
		SetState(SIMON_STATE_IDLE_UP_STAIR);
		break;
	case SIMON_STATE_GO_DOWN_STAIR:
		SetState(SIMON_STATE_IDLE_DOWN_STAIR);
		break;
	}
}

void Simon::moveRight(DWORD dt)
{
	state = SIMON_STATE_WALKING_RIGHT;
	x += 0.025 * dt;
}

void Simon::SetupAtacking()
{
	if (attacking)
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
}

void Simon::SetupSubWeapon(vector<LPGAMEOBJECT>* coObjects)
{
	if (enableSubWeapon && startThrowWeapon == 0 && baseInfo->getHeart() > 0)
	{
		if (baseInfo->getIdSubWeapon() != NULL)
		{
			if (baseInfo->getIdSubWeapon() == ID_ENTITY_STOP_WATCH)
			{
				Enemy::StopWatchStart();
			}
			else
			{
				baseInfo->getSubWeapon()->SetState(STATE_SHOW);
				if (state == SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON)
				{
					baseInfo->getSubWeapon()->SetPosition(D3DXVECTOR2(x, y + 30));
				}
				else
				{
					baseInfo->getSubWeapon()->SetPosition(D3DXVECTOR2(x, y));
				}
				baseInfo->getSubWeapon()->set_nx(nx);
				coObjects->push_back(baseInfo->getSubWeapon());
				startThrowWeapon = GetTickCount();
			}
			baseInfo->setHeart(max(0,baseInfo->getHeart() - 1));
		}
	}
}

void Simon::RenderWeapon(LPANIMATION animation, Viewport * viewport)
{
	if (attacking)
	{
		whip->updatePostision(animation->getCurrentFrame(), currentAnimation, flip);
		whip->draw(flip, viewport);
	}
	else
	{
		whip->SetPosition(D3DXVECTOR2(x, y));
	}
}

void Simon::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (attacking)
	{
		whip->Update(dt, coObjects);

		if (startAtack == 0)
		{
			startAtack = GetTickCount();
		}
		else if (startAtack > 0 && GetTickCount() - startAtack > 450)
		{
			Reset(currentAnimation);
			startAtack = 0;
		}
	}

	if (enableSubWeapon)
	{
		if (startAtackSub == 0)
		{
			startAtackSub = GetTickCount();
		}
		else if (startAtackSub > 0 && GetTickCount() - startAtackSub > 450)
		{
			SetState(SIMON_STATE_IDLE);
			animations.find(currentAnimation)->second->SetFinish(false);
			startAtackSub = 0;
		}
	}

	if (baseInfo->getIdSubWeapon() != ID_ENTITY_NULL)
	{
		if (GetTickCount() - startThrowWeapon > 450 && startThrowWeapon > 0 && enableSubWeapon)
		{
			enableSubWeapon = false;
			startThrowWeapon = 0;
			baseInfo->setIdSubWeapon(baseInfo->getIdSubWeapon());
		}
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 20;
	top = y;
	right = left + width / 2;
	bottom = top + height;
}

void Simon::Render(Viewport* viewport)
{
	RenderBoundingBox(viewport);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	LPANIMATION animation = animations.find(currentAnimation)->second;
	DebugOut(L"state:{%d}\n", state);

	DebugOut(L"animation:{%d}\n", currentAnimation);

	if (animation)
	{
		if (nx == 1) flip = normal;
		else flip = flip_horiz;

		if (isOnStair)
		{
			if (state == SIMON_STATE_GO_DOWN_STAIR || state == SIMON_STATE_IDLE_DOWN_STAIR
				|| state == SIMON_STATE_ATTACK_DOWN_STAIR)
			{
				if (nx > 0 && originalStair->get_ny() > 0)
				{
					flip = flip_horiz;
				}
				else if (nx < 0 && originalStair->get_ny()  > 0)
				{
					flip = normal;
				}
			}
			else if (state == SIMON_STATE_GO_UP_STAIR || state == SIMON_STATE_IDLE_UP_STAIR
				|| state == SIMON_STATE_ATTACK_UP_STAIR)
			{
				if (nx < 0 && originalStair->get_ny() < 0)
				{
					flip = normal;
				}
				else if (nx > 0 && originalStair->get_ny() < 0)
				{
					flip = flip_horiz;
				}
			}
		}

		if (checkInsideViewPort(viewport))
		{ 
			if (!untouchable && !isVisible)
			{
				animation->Render(pos.x, pos.y, flip);
			}
			else if (untouchable)
			{
				int alpha = rand() % 100 > 50 ? 80 : 170;
				animation->Render(pos.x, pos.y, flip, alpha);
			} 
			else if (isVisible)
			{
				int alpha = 0;
				animation->Render(pos.x, pos.y, flip, alpha);
			}
		}
		else return;
	}
	RenderWeapon(animation, viewport);
}

bool Simon::isMovedEndMap()
{
	return hasMovedEndMap;
}

void Simon::SetStateMoveEndMap(bool hasMovedMap)
{
	this->hasMovedEndMap = hasMovedMap;
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
		attacking = false;
		nx = 1;
		checkRewind = true;
		currentAnimation = SIMON_ANI_WALKING;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		attacking = false;
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
		attacking = false;
		break;

	case SIMON_STATE_ATTACK_JUMP:
		enableSubWeapon = false;
		attacking = true;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_ATTACK_JUMP_SUBWEAPON:
		enableSubWeapon = true;
		attacking = false;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_ATTACK_STAND:
		enableSubWeapon = false;
		vx = 0;
		attacking = true;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_ATTACK_STAND_SUBWEAPON:
		vx = 0;
		enableSubWeapon = true;
		attacking = false;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_SITDOWN:
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_SITDOWN;
		break;

	case SIMON_STATE_ATTACK_SITDOWN:
		enableSubWeapon = false;
		attacking = true;
		vx = 0;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
		break;

	case SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON:
		enableSubWeapon = true;
		attacking = true;
		vx = 0;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		isOnStair = false;
		attacking = false;
		enableSubWeapon = false;
		checkRewind = false;
		currentAnimation = SIMON_ANI_IDLE;
		originalStair = nullptr;
		isjumping = false;
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
		isOnStair = true;
		set_nx(originalStair->get_nx());
		SetSpeed(originalStair->get_nx()*SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		if (originalStair->get_ny() < 0)
		{
			SetSpeed(-nx*SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		}
		currentAnimation = SIMON_ANI_GO_UP_STAIR;
		break;

	case SIMON_STATE_GO_DOWN_STAIR:
		checkRewind = true;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		SetSpeed(originalStair->get_nx()*(SIMON_STAIR_SPEED), SIMON_STAIR_SPEED);
		if (originalStair->get_ny() > 0)
		{
			SetSpeed(-nx* SIMON_STAIR_SPEED, SIMON_STAIR_SPEED);
		}
		currentAnimation = SIMON_ANI_GO_DOWN_STAIR;
		break;

	case SIMON_STATE_IDLE_UP_STAIR:
		SetSpeed(0, 0);
		attacking = false;
		isOnStair = true;
		currentAnimation = SIMON_ANI_IDLE_GO_UP_STAIR;
		break;

	case SIMON_STATE_IDLE_DOWN_STAIR:
		SetSpeed(0, 0);
		isOnStair = true;
		attacking = false;
		currentAnimation = SIMON_ANI_IDLE_GO_DOWN_STAIR;
		break;

	case SIMON_STATE_ATTACK_UP_STAIR:
		attacking = true;
		enableSubWeapon = false;
		checkRewind = true;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		currentAnimation = SIMON_ANI_ATTACK_UP_STAIR;
		break;

	case SIMON_STATE_ATTACK_DOWN_STAIR:
		attacking = true;
		checkRewind = true;
		enableSubWeapon = false;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		currentAnimation = SIMON_ANI_ATTACK_DOWN_STAIR;
		break;

	case SIMON_STATE_HURT:
		attacking = false;
		if (!isjumping && isOnGround()&& !isOnStair)
		{
 			isjumping = true;
			vy = -SIMON_HURT_SPEED_Y;
			vx = -nx * SIMON_MOVE_SPEED;
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
		checkRewind = true;
		animations.find(currentAnimation)->second->SetFinish(false);
		break;
	}
	animations.find(currentAnimation)->second->SetLoop(checkRewind);
	DebugOut(L"state:{%d}\n", state);
}

void Simon::Reset(int currentAnimation)
{
	switch (currentAnimation)
	{
	case SIMON_ANI_GO_UP_STAIR:
	case SIMON_ANI_ATTACK_UP_STAIR:
		SetState(SIMON_STATE_IDLE_UP_STAIR);
		attacking = false;
		break;
	case SIMON_ANI_GO_DOWN_STAIR:
	case SIMON_ANI_ATTACK_DOWN_STAIR:
		SetState(SIMON_STATE_IDLE_DOWN_STAIR);
		attacking = false;
		break;
	case SIMON_ANI_SITDOWN:
	case SIMON_ANI_ATTACK_SITDOWN:
		SetState(SIMON_STATE_SITDOWN);
		attacking = false;
		break;
	default:
		SetState(SIMON_STATE_IDLE);
		attacking = false;
		break;
	}

	if (!enableSubWeapon)
	{
		whip->animations.find(whip->getCurrentAnimation())->second->SetFinish(false);
	}	
	animations.find(currentAnimation)->second->SetFinish(false);
}

void Simon::updateCollisionStair()
{
	if (isOnStair)
	{
		if(originalStair->get_ny() > 0 && (y + height <= (originalStair->getPosition().y + originalStair->getInfoStair().y - originalStair->getHeight()))
		|| originalStair->get_ny() < 0 && (y + height >= (originalStair->getPosition().y + originalStair->getHeight())))
		{
			handleOutOfStair();
		}
	}
}

void Simon::handleOutOfStair() {
	if (state == SIMON_STATE_GO_DOWN_STAIR || state == SIMON_STATE_IDLE_DOWN_STAIR
		|| state == SIMON_STATE_ATTACK_DOWN_STAIR)
	{
		if (originalStair->get_ny() > 0)
		{
			nx = -nx;
		}
	}
	else if (state == SIMON_STATE_GO_UP_STAIR || state == SIMON_STATE_IDLE_UP_STAIR
		|| state == SIMON_STATE_ATTACK_UP_STAIR)
	{
		if (originalStair->get_ny() < 0)
		{
			nx = -nx;
		}
	}
	SetState(SIMON_STATE_IDLE);
}

void Simon::updateCollisionSubStair()
{
	if (isOnStair)
	{
		if (originalStair->get_ny() > 0 && (y + height <= (originalStair->getPosition().y + originalStair->getInfoStair().y - originalStair->getHeight())
			|| y + height >= originalStair->getPosition().y)
			|| originalStair->get_ny() < 0 && (y + height >= (originalStair->getPosition().y + originalStair->getHeight()) 
			|| y + height <= originalStair->getPosition().y + originalStair->getInfoStair().y))
		{
  			handleOutOfStair();
		}
	}
}

void Simon::handleCollisionObjectGame(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!isOnStair)
	{
		vy += SIMON_GRAVITY * dt;
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
		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;
		handleCollisionIntersectedObject(dt, coObjects);
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (int i = 0; i < (int)coEvents.size(); i++)
		{
			switch (coEvents[i]->obj->getID())
			{
			case ID_ENTITY_BRICK:
				if (coEvents[i]->obj->getName().compare("SmallBrick") == 0)
				{
					if (ny < 0)
					{
						vy = 0;
						Dy = min_ty * dy + ny * 0.1f;
					}
				}
				else
				{
					Dx = min_tx * dx + nx * 0.11f;
					if (nx != 0) vx = 0;
				}
				break;
			case ID_ENTITY_ENTRANCE:
				comeEntranceStart = GetTickCount();
				break;
			case ID_ENTITY_WALL_ENTRANCE:
				if (coEvents[i]->obj->getName()
					.compare("ActivateWall") == 0)
				{
					DarkBat::ActivateState();
					if (ny != 0) vy = 0;
					Dy = min_ty * dy + ny * 0.1f;
					Dx = min_tx * dx + nx * 0.11f;
					if (nx != 0) vx = 0;
				}
				else if (coEvents[i]->obj->getName().compare("Wall")==0)
				{
					if (ny != 0) vy = 0;
					Dy = min_ty * dy + ny * 0.1f;
					Dx = min_tx * dx + nx * 0.11f;
					if (nx != 0) vx = 0;
				}
				break;
			case ID_ENTITY_FLOOR:
				if (!isOnStair)
				{
					if (coEvents[i]->obj->getName().compare("HighFloor") == 0)
					{
						if (ny < 0)
						{
							vy = 0;
							Dy = min_ty * dy + ny * 0.1f;
						}
					}
					else if (coEvents[i]->obj->getName().compare("Floor") == 0)
					{
						if (ny != 0) vy = 0;
						Dy = min_ty * dy + ny * 0.11f;
					}
					if (coEvents[i]->obj->getName().compare("Water") == 0)
					{
						WaterEffect* effect = new WaterEffect(getPosition());
						coObjects->push_back(effect);
					}
				}
				break;
			case ID_ENTITY_DOOR:
				for (int j = 0; j < (int)coObjects->size(); j++)
				{
					if (coEvents[i]->obj->getName().compare("FirstDoor")==0)
					{
						switch (coObjects->at(j)->getID())
						{
						case ID_ENTITY_ZOMBIE:
						case ID_ENTITY_PANTHER:
							coObjects->at(j)->SetState(STATE_DETROY);
								break;
						}
					}
					else if (coEvents[i]->obj->getName().compare("SecondDoor") == 0)
					{
						switch (coObjects->at(j)->getID())
						{
						case ID_ENTITY_VAMPIRE_BAT:
							coObjects->at(j)->SetState(STATE_DETROY);
							break;
						}
					}
				}
				SetState(SIMON_STATE_IDLE);
				Dx = min_tx * dx + nx * 0.11f;
				Door::startAction();
				break;
			}
		}
		x += Dx;
		y += Dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::handleAfterCollision(vector <LPGAMEOBJECT>* coObjects, EntityID id, int i, vector<LPCOLLISIONEVENT> *coEvents)
{
	switch (id)
	{
	case ID_ENTITY_ZOMBIE:
	case ID_ENTITY_FISH_MAN:
	case ID_ENTITY_CRYSTAL_BALL:
	case ID_ENTITY_VAMPIRE_BAT:
	case ID_ENTITY_DARK_BAT:
		if (!untouchable && !isVisible)
		{
			SetState(SIMON_STATE_HURT);
			baseInfo->setHealth(max(0,baseInfo->getHealth() - 1));
			StartUntouchable();
		}
		break;
	case ID_ENTITY_WEAPON_REWARD:
		SetState(SIMON_STATE_CHANGECOLOR);
		if (levelWhip == 1)
		{
			levelWhip = 2;
		}
		else if (levelWhip == 2)
		{
			levelWhip = 3;
		}
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_HEART:
		baseInfo->setHeart(baseInfo->getHeart() + 10);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_STOP_WATCH:
		baseInfo->setIdSubWeapon(ID_ENTITY_STOP_WATCH);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_FIRE_BOMB:
		baseInfo->setIdSubWeapon(ID_ENTITY_FIRE_BOMP_WEAPON);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_CROSS:
		TiledMap::CreateEffectStart();
		for (int j = 0; j < (int)coObjects->size(); j++)
		{
			switch (coObjects->at(j)->getID())
			{
			case ID_ENTITY_ZOMBIE:
			case ID_ENTITY_PANTHER:
				coObjects->at(j)->SetState(STATE_DETROY);
				break;
			}
		}
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_DAGGER:
		baseInfo->setIdSubWeapon(ID_ENTITY_DAGGER_WEAPON);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_INVISIBILITY_POTION:
		isVisible = true;
		if (invisible_Potion_Start == 0)
		{
			invisible_Potion_Start = GetTickCount();
		} 
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_AXE:
		baseInfo->setIdSubWeapon(ID_ENTITY_AXE_WEAPON);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_SMALL_HEART:
		baseInfo->setHeart(baseInfo->getHeart() + 1);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_PORK_CHOP:
		baseInfo->setHeart(baseInfo->getHeart() + 10);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_MIRACULOUS_BAG:
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_EFFECT);
			coObjects->at(i)->SetPosition(D3DXVECTOR2(x, y + 20));
		}
		break;
	case ID_ENTITY_STAIR:
		if (!isOnStair)
		{
			originalStair = new ObjectStair(dynamic_cast<ObjectStair*>(coObjects->at(i)));
		}
		break;
	case ID_ENTITY_PANTHER:
		Panther* panther = dynamic_cast<Panther*>(coObjects->at(i));
		if (!panther->IsActivate())
		{
			panther->setActivate(true);
		}
		else if(!untouchable && !isVisible)
		{
			SetState(SIMON_STATE_HURT);
			baseInfo->setHealth(max(0, baseInfo->getHealth() - 1));
			StartUntouchable();
		}
		break;
	}
}

void Simon::handleCollisionIntersectedObject(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float l, t, r, b;
	float l2, t2, r2, b2;
	RECT rect1;
	RECT rect2;
	for (int i = 0; i < (int)coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_PANTHER 
			&& coObjects->at(i)->GetState() != Panther::PANTHER_STATE_ACTIVATE)
		{
			Panther* panther = nullptr;
			panther = dynamic_cast<Panther*>(coObjects->at(i));
			if (!panther->IsActivate())
			{
				if (nx > 0)
				{
					rect1 = panther->getBBActivateRight();
				}
				else if (nx < 0)
				{
					rect1 = panther->getBBActivateLeft();
				}
			}
		}
		else
		{
			coObjects->at(i)->GetBoundingBox(l, t, r, b);
			rect1 = RECT{ long(l), long(t), long(r), long(b) };
		}
		GetBoundingBox(l2, t2, r2, b2);
		rect2 = RECT{ long(l2), long(t2), long(r2), long(b2) };
		bool result = this->checkCollision(rect1, rect2);

		if (result)
		{
			handleAfterCollision(coObjects, coObjects->at(i)->getID(), i, nullptr);
		}
	}
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

