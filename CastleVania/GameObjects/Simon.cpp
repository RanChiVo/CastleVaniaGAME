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
#include "../Flip.h"
#include "../GameObjects/Zombie.h"
#include "../Panther.h"
#include "../Door.h"
#include "../Viewport.h"
#include "../WaterEffect.h"
#include "../DarkBat.h"
#include "../BallDarkBat.h"
#include "../Boomerang.h"
#include "../TiledMap.h"
#include "../Portal.h"
#include "../Game.h"
#include "../PortalPosMap.h"
#include "../ActivationBox.h"
#include "../Crown.h"
#include "../MovingBrick.h"

constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.42f;
constexpr float SIMON_MOVE_SPEED = 0.12f;
constexpr float SIMON_AUTO_SPEED_RIGHT = 0.025f;
constexpr float SIMON_GRAVITY = 0.001f;
constexpr float SIMON_HURT_SPEED_Y = 0.2f;
constexpr float SIMON_STAIR_SPEED = 0.06f;
constexpr DWORD SIMON_ENTRANCE_TIME = 5000;
constexpr DWORD INVISIBLE_TIME = 4000;
constexpr DWORD SIMON_UNTOUCHABLE_TIME = 2000;
constexpr DWORD SIMON_PROTECT_TIME = 2000;
constexpr DWORD SIMON_HURT_TIME = 1000;
constexpr DWORD SIMON_DIE_TIME = 3000;
constexpr DWORD SIMON_CHANGE_COLOR_TIME = 1500;

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
	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	comeEntranceStart = 0;
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

	updateCollisionStair();

	updateCollisionSubStair();

	handleCollisionObjectGame(dt, coObjects);

	if (comeEntranceStart > 0 && GetTickCount() - comeEntranceStart > SIMON_ENTRANCE_TIME)
	{
		comeEntranceStart = 0;
		isMovingDoor = false;
		SetState(SIMON_STATE_IDLE);
	}

	if (startHurt > 0 && GetTickCount() - startHurt > SIMON_HURT_TIME)
	{
		startHurt = 0;
	}

	if (invisible_Potion_Start > 0 && GetTickCount() - invisible_Potion_Start > INVISIBLE_TIME)
	{
		invisible_Potion_Start = 0;
		isVisible = false;
	}

	if (baseInfo->getHealth() == 0 && startDie == 0)
	{
		SetState(SIMON_STATE_DIE);
		startDie = GetTickCount();
	}

	if (startDie > 0 && GetTickCount() - startDie > SIMON_DIE_TIME)
	{
		startDie = 0;
		resetWhenDie();
	}

	if (startChangeColor > 0 && GetTickCount() - startChangeColor > SIMON_CHANGE_COLOR_TIME)
	{
		SetState(SIMON_STATE_IDLE);
		startChangeColor = 0;
	}
}

void Simon::SetState(int state)
{
	this->state = state;
}

void Simon::OnKeyStateChange(BYTE * states)//state
{
	if (state == SIMON_STATE_AUTO_GOES_RIGHT || state == SIMON_STATE_CHANGECOLOR)
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
				if (originalStair->Get_nyStair() > 0)
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
				if (originalStair->Get_nyStair() < 0)
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
	case SIMON_STATE_HURT:
		if (originalStair)
		{
			if (directInput->IsKeyDown(DIK_UP))
			{
				if (originalStair->Get_nyStair() > 0)
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
				if (originalStair->Get_nyStair() < 0)
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
					startAtack = GetTickCount();
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
					startAtack = GetTickCount();
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


	if (state == SIMON_STATE_AUTO_GOES_RIGHT || state == SIMON_STATE_CHANGECOLOR)
	{
		return;
	}
	switch (state)
	{
	case SIMON_STATE_IDLE:
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (KeyCode == DIK_X) SetState(SIMON_STATE_JUMPING);
		if (KeyCode == DIK_Z && !directInput->IsKeyDown(DIK_UP))
		{
			SetState(SIMON_STATE_ATTACK_STAND);
			startAtack = GetTickCount();

		}
		else if (KeyCode == DIK_Z && directInput->IsKeyDown(DIK_UP))
		{
			SetState(SIMON_STATE_ATTACK_STAND_SUBWEAPON);
			startAtackSub = GetTickCount();
		}
		break;
	case SIMON_STATE_JUMPING:
		if (KeyCode == DIK_Z && !directInput->IsKeyDown(DIK_UP))
		{
			SetState(SIMON_STATE_ATTACK_JUMP);
			startAtack = GetTickCount();

		}
		else if (KeyCode == DIK_Z && directInput->IsKeyDown(DIK_UP))
		{
			startAtackSub = GetTickCount();
			SetState(SIMON_STATE_ATTACK_JUMP_SUBWEAPON);
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
			startAtack = GetTickCount();
		}
		else if (KeyCode == DIK_Z && directInput->IsKeyDown(DIK_UP))
		{
			startAtackSub = GetTickCount();
			SetState(SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON);
		}
		break;
	}
}

void Simon::OnKeyUp(int KeyCode)
{
	if (state == SIMON_STATE_AUTO_GOES_RIGHT || state == SIMON_STATE_CHANGECOLOR)
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

void Simon::SetupAtacking()
{
	if (startAtack)
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
			baseInfo->setHeart(max(0, baseInfo->getHeart() - 1));
		}
	}
}

void Simon::RenderWeapon(LPANIMATION animation, Viewport * viewport)
{
	if (startAtack && state!=SIMON_STATE_HURT)
	{
		whip->updatePostision(animation->getCurrentFrame(), currentAnimation, flip);
		whip->draw(flip, viewport);
	}
}

void Simon::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (startAtack)
	{
		whip->Update(dt, coObjects);

		if (startAtack > 0 && GetTickCount() - startAtack > 400)
		{
			Reset(currentAnimation);
			startAtack = 0;
		}
	}

	if (startAtackSub)
	{

		if (baseInfo->getIdSubWeapon() == ID_ENTITY_BOOMERANG_WEAPON)
		{
			baseInfo->getSubWeapon()->setLiveTime(GetTickCount());
		}
		if (startAtackSub > 0 && GetTickCount() - startAtackSub > 400)
		{
			SetState(SIMON_STATE_IDLE);
			animation_set->find(currentAnimation)->second->SetFinish(false);
			startAtackSub = 0;
		}
	}

	if (baseInfo->getIdSubWeapon() != ID_ENTITY_NULL)
	{
		if (GetTickCount() - startThrowWeapon > 400 && startThrowWeapon > 0 && enableSubWeapon)
		{
			enableSubWeapon = false;
			startThrowWeapon = 0;
			baseInfo->setIdSubWeapon(baseInfo->getIdSubWeapon());
		}
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{ 
	if (state == SIMON_STATE_JUMPING)
	{
		left = x + 8;
		top = y + 7;
		right = left + width - 18;
		bottom = top + height - 20;
	}
	left = x + 8;
	top = y;
	right = left + width - 18 ;
	bottom = top + height;
}

void Simon::Render(Viewport* viewport)
{
	RenderBoundingBox(viewport);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	LPANIMATION animation = animation_set->find(currentAnimation)->second;
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
				if (nx > 0 && originalStair->Get_nyStair() > 0)
				{
					flip = flip_horiz;
				}
				else if (nx < 0 && originalStair->Get_nyStair()  > 0)
				{
					flip = normal;
				}
			}
			else if (state == SIMON_STATE_GO_UP_STAIR || state == SIMON_STATE_IDLE_UP_STAIR
				|| state == SIMON_STATE_ATTACK_UP_STAIR)
			{
				if (nx < 0 && originalStair->Get_nyStair() < 0)
				{
					flip = normal;
				}
				else if (nx > 0 && originalStair->Get_nyStair() < 0)
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
	case SIMON_STATE_AUTO_GOES_RIGHT:
		vx = SIMON_AUTO_SPEED_RIGHT;
		nx = 1;
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
		enableSubWeapon = false;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_ATTACK_JUMP_SUBWEAPON:
		enableSubWeapon = true;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_ATTACK_STAND:
		enableSubWeapon = false;
		vx = 0;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		break;

	case SIMON_STATE_ATTACK_STAND_SUBWEAPON:
		vx = 0;
		enableSubWeapon = true;
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
		vx = 0;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
		break;

	case SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON:
		enableSubWeapon = true;
		vx = 0;
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		isOnStair = false;
		enableSubWeapon = false;
		checkRewind = false;
		currentAnimation = SIMON_ANI_IDLE;
		originalStair = nullptr;
		isjumping = false;
		break;

	case SIMON_STATE_CHANGECOLOR:

		vx = 0;
		checkRewind = true;
		if (changeColorId)
		{
			changeColorId = 0;
			currentAnimation = SIMON_ANI_COLOR;
		}
		else {
			changeColorId = 1;
			currentAnimation = SIMON_ANI_COLOR1;
		}
		break;

	case SIMON_STATE_GO_UP_STAIR:
		checkRewind = true;
		isOnStair = true;
		set_nx(originalStair->Get_nxStair());
		SetSpeed(originalStair->Get_nxStair()*SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		if (originalStair->Get_nyStair() < 0)
		{
			SetSpeed(-nx * SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		}
		currentAnimation = SIMON_ANI_GO_UP_STAIR;
		break;

	case SIMON_STATE_GO_DOWN_STAIR:
		checkRewind = true;
		isOnStair = true;
		set_nx(originalStair->Get_nxStair());
		SetSpeed(originalStair->Get_nxStair()*(SIMON_STAIR_SPEED), SIMON_STAIR_SPEED);
		if (originalStair->Get_nyStair() > 0)
		{
			SetSpeed(-nx * SIMON_STAIR_SPEED, SIMON_STAIR_SPEED);
		}
		currentAnimation = SIMON_ANI_GO_DOWN_STAIR;
		break;

	case SIMON_STATE_IDLE_UP_STAIR:
		SetSpeed(0, 0);
		isOnStair = true;
		currentAnimation = SIMON_ANI_IDLE_GO_UP_STAIR;
		break;

	case SIMON_STATE_IDLE_DOWN_STAIR:
		SetSpeed(0, 0);
		isOnStair = true;
		currentAnimation = SIMON_ANI_IDLE_GO_DOWN_STAIR;
		break;

	case SIMON_STATE_ATTACK_UP_STAIR:
		enableSubWeapon = false;
		checkRewind = true;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		currentAnimation = SIMON_ANI_ATTACK_UP_STAIR;
		break;

	case SIMON_STATE_DIE:
		vx = 0;
		isOnStair = false;
		enableSubWeapon = false;
		checkRewind = false;
		currentAnimation = SIMON_ANI_DEAD;
		originalStair = nullptr;
		isjumping = false;
		break;

	case SIMON_STATE_ATTACK_DOWN_STAIR:
		checkRewind = true;
		enableSubWeapon = false;
		isOnStair = true;
		set_nx(originalStair->Get_nxStair());
		currentAnimation = SIMON_ANI_ATTACK_DOWN_STAIR;
		break;

	case SIMON_STATE_HURT:
		if (!isjumping && isOnGround() && !isOnStair)
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
		animation_set->find(ani)->second->SetFinish(false);
		break;
	}
	animation_set->find(currentAnimation)->second->SetLoop(checkRewind);
	DebugOut(L"state:{%d}\n", state);
}

void Simon::Reset(int currentAnimation)
{
	switch (currentAnimation)
	{
	case SIMON_ANI_GO_UP_STAIR:
	case SIMON_ANI_ATTACK_UP_STAIR:
		SetState(SIMON_STATE_IDLE_UP_STAIR);
		break;
	case SIMON_ANI_GO_DOWN_STAIR:
	case SIMON_ANI_ATTACK_DOWN_STAIR:
		SetState(SIMON_STATE_IDLE_DOWN_STAIR);
		break;
	case SIMON_ANI_SITDOWN:
	case SIMON_ANI_ATTACK_SITDOWN:
		SetState(SIMON_STATE_SITDOWN);
		break;
	default:
		SetState(SIMON_STATE_IDLE);
		break;
	}

	if (!enableSubWeapon)
	{
		whip->GetAnimationSet()->find(whip->getCurrentAnimation())->second->SetFinish(false);

	}
	animation_set->find(currentAnimation)->second->SetFinish(false);
}

void Simon::updateCollisionStair()
{
	if (isOnStair)
	{
		if (originalStair->Get_nyStair() > 0 && (y + height <= (originalStair->getPosition().y + originalStair->getHeight()
			- originalStair->GetHeightStair()))
			|| originalStair->Get_nyStair() < 0 && (y + height >= (originalStair->getPosition().y + originalStair->GetHeightStair())))
		{
			handleOutOfStair();
		}
	}
}

void Simon::handleOutOfStair() {
	if (state == SIMON_STATE_GO_DOWN_STAIR || state == SIMON_STATE_IDLE_DOWN_STAIR
		|| state == SIMON_STATE_ATTACK_DOWN_STAIR)
	{
		if (originalStair->Get_nyStair() > 0)
		{
			nx = -nx;
		}
	}
	else if (state == SIMON_STATE_GO_UP_STAIR || state == SIMON_STATE_IDLE_UP_STAIR
		|| state == SIMON_STATE_ATTACK_UP_STAIR)
	{
		if (originalStair->Get_nyStair() < 0)
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
		if (originalStair->Get_nyStair() > 0 && (y + height <= (originalStair->getPosition().y + originalStair->getHeight() - originalStair->GetHeightStair())
			|| y + height >= originalStair->getPosition().y)
			|| originalStair->Get_nyStair() < 0 && (y + height >= (originalStair->getPosition().y + originalStair->GetHeightStair())
				|| y + height <= originalStair->getPosition().y + originalStair->getHeight()))
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

	vector<LPGAMEOBJECT> staticObject;

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_WALL
			|| coObjects->at(i)->getID() == ID_ENTITY_FLOOR ||
			coObjects->at(i)->getID() == ID_ENTITY_BRICK 
			||coObjects->at(i)->getID() == ID_ENTITY_MOVING_BRICK)
			staticObject.push_back(coObjects->at(i));
	}

	// Handle collision between simon with wall

	CalcPotentialCollisions(&staticObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (!isOnStair)
		{
			x += min_tx * dx + nx * 0.1f;
		}
		else x += dx;

		if (nx != 0) vx = 0;

		y += min_ty * dy + ny * 0.1f;

		if (ny < 0 && !isOnStair)
		{
			vy = 0;
		}
		else y += dy;
	}
	coEvents.clear();


	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	handleCollisionIntersectedObject(dt, coObjects, &coEvents);

	for (int i = 0; i < (int)coEvents.size(); i++)
	{
		switch (coEvents[i]->obj->getID())
		{
		case ID_ENTITY_PORTAL:
		{
			Portal *p = dynamic_cast<Portal *>(coEvents[i]->obj);
			Game::GetInstance()->SwitchScene(p->GetSceneId());
		}
		break;
		case ID_ENTITY_PORTAL_POS_MAP:
		{
			PortalPosMap *ps = dynamic_cast<PortalPosMap *>(coEvents[i]->obj);
			Direct3DManager::getInstance()->getViewport()->setStartViewPortX(ps->GetStartViewportX());
			Direct3DManager::getInstance()->getViewport()->setEndViewPortX(ps->GetEndViewportX());
		}
		break;
		case ID_ENTITY_ENTRANCE:
		{
			comeEntranceStart = GetTickCount();
			SetState(SIMON_STATE_AUTO_GOES_RIGHT);
		}
		break;
		case ID_ENTITY_MOVING_BRICK:
		{
			MovingBrick *movingBrick = dynamic_cast<MovingBrick *>(coEvents[i]->obj);
			float vxBr, vyBr;
			movingBrick->GetSpeed(vxBr, vyBr);
			SetSpeed(vxBr*2, vy);
		}
		break;
		}
	}
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
	case ID_ENTITY_SPEAR_KNIGHT:
	case ID_ENTITY_GHOST:

		if (!untouchable && !isVisible)
		{
			SetState(SIMON_STATE_HURT);
			baseInfo->setHealth(max(0, baseInfo->getHealth() - 1));
			StartUntouchable();
		}
		break;
	case ID_ENTITY_WEAPON_REWARD:
		SetState(SIMON_STATE_CHANGECOLOR);
		if (startChangeColor == 0)
		{
			startChangeColor = GetTickCount();
		}
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
		break;
	case ID_ENTITY_BOOMERANG:
		baseInfo->setIdSubWeapon(ID_ENTITY_BOOMERANG_WEAPON);
		if (coObjects)
		{
			coObjects->at(i)->SetState(STATE_DETROY);
		}
		else
		{
			coEvents->at(i)->obj->SetState(STATE_DETROY);
		}
		break;
	case ID_ENTITY_BALL_DARK_BAT:
		if (coObjects)
		{
			if (coObjects->at(i)->IsTouched())
			{
				coObjects->at(i)->SetState(STATE_DETROY);
			}
		}
		else
		{
			if (coEvents->at(i)->obj->IsTouched())
			{
				coEvents->at(i)->obj->SetState(STATE_DETROY);
			}
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
			MiraculousBag* money = dynamic_cast<MiraculousBag*>(coObjects->at(i));
			money->SetState(STATE_EFFECT);
			money->SetPosition(D3DXVECTOR2(x, y + 20));
			baseInfo->setScore(money->getScore());
		}
		break;
	case ID_ENTITY_CROWN:
		if (coObjects)
		{
			Crown* crown = dynamic_cast<Crown*>(coObjects->at(i));
			crown->SetState(STATE_EFFECT);
			crown->setTimeEffect(GetTickCount());
		}
		break;
	case ID_ENTITY_STAIR:
		if (!isOnStair)
		{
			originalStair = new ObjectStair(dynamic_cast<ObjectStair*>(coObjects->at(i)));
		}
		break;
	case ID_ENTITY_PANTHER:
	{
		Panther* panther = dynamic_cast<Panther*>(coObjects->at(i));
		if (!panther->IsActivate())
		{
			panther->setActivate(true);
		}
		else if (!untouchable && !isVisible)
		{
			SetState(SIMON_STATE_HURT);
			baseInfo->setHealth(max(0, baseInfo->getHealth() - 1));
			StartUntouchable();
		}
	}
	break;
	case ID_ENTITY_ACTIVATEBOX:
	{
		ActivationBox *actionBox = dynamic_cast<ActivationBox *>(coObjects->at(i));
		actionBox->ActionObject(coObjects);
		if (actionBox->GetActivatedObjecId() != ID_ENTITY_VAMPIRE_BAT)
		{
			actionBox->SetState(STATE_DETROY);
		}
	}
	break;

	}
}

void Simon::handleCollisionIntersectedObject(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> *coEvents)
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
			handleAfterCollision(coObjects, coObjects->at(i)->getID(), i, coEvents);
		}
	}
}

void Simon::resetWhenDie()
{
	baseInfo->setHealth(4);
	SetPosition(resetPosition);
	MovingMap::getInstance()->setIdMap(Utils::getInstance()->getStringToEntityID()[getIdHiddenItem()]);
	Direct3DManager::getInstance()->getViewport()->setStartViewPortX(getStartViewPort());
	Direct3DManager::getInstance()->getViewport()->setEndViewPortX(getEndViewPort());
	SetState(SIMON_STATE_IDLE);
	set_nx(1);
}

void Simon::setResetPosition(D3DXVECTOR2 pos)
{
	this->resetPosition = pos;
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

