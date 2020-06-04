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
constexpr float SIMON_JUMP_SPEED_Y = 0.38f;
constexpr float SIMON_MOVE_SPEED = 0.12f;
constexpr float SIMON_AUTO_SPEED_RIGHT = 0.025f;
constexpr float SIMON_GRAVITY = 0.001f;
constexpr float SIMON_HURT_SPEED_Y = 0.28f;
constexpr float SIMON_STAIR_SPEED = 0.06f;
constexpr DWORD SIMON_ENTRANCE_TIME = 5000;
constexpr DWORD INVISIBLE_TIME = 4000;
constexpr DWORD SIMON_UNTOUCHABLE_TIME = 2000;
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
	id = ID_ENTITY_SIMON;
	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	comeEntranceStart = 0;
	WHIP_STATE = 1;
	levelWhip = 1;
	baseInfo = new BaseInfo();
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);

	UpdateWeapon(dt, coObjects);

	SetupAtacking();

	SetupSubWeapon(coObjects);

	UpdateGotoStair();

	updateCollisionSubStair();

	handleCollisionObjectGame(dt, coObjects);

	if (comeEntranceStart > 0 && GetTickCount() - comeEntranceStart > SIMON_ENTRANCE_TIME)
	{
		comeEntranceStart = 0;
		SetState(SIMON_STATE_IDLE);
	}

	if (invisible_Potion_Start > 0 && GetTickCount() - invisible_Potion_Start > INVISIBLE_TIME)
	{
		invisible_Potion_Start = 0;
		isVisible = false;
	}

	if (untouchable_start > 0 && GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
		SetState(SIMON_STATE_IDLE);
	}

	if (baseInfo->getHealth() == 0 && timeDie == 0)
	{
		SetState(SIMON_STATE_DIE);
		timeDie = GetTickCount();
	}

	if (timeDie > 0 && GetTickCount() - timeDie > SIMON_DIE_TIME)
	{
		timeDie = 0;
		resetWhenDie();
	}

	if (timeChangeColor > 0 && GetTickCount() - timeChangeColor > SIMON_CHANGE_COLOR_TIME)
	{
		SetState(SIMON_STATE_IDLE);
		timeChangeColor = 0;
	}

	if (timeAutoGoStair> 0 && (GetTickCount() - timeAutoGoStair) >= 200)
	{
		isGoingAutoStair = false;
		timeAutoGoStair = 0;
		if (temporaryState == SIMON_STATE_GO_DOWN_STAIR)
		{
			SetState(Simon::State::SIMON_STATE_IDLE_DOWN_STAIR);
		}
		else SetState(Simon::State::SIMON_STATE_IDLE_UP_STAIR);
	}

	if (startJumpingSitFloor > 0 && GetTickCount() - startJumpingSitFloor > 100)
	{
		startJumpingSitFloor = 0;
	}

	if (highFloor && highFloor->getName().compare("HighFloor") == 0)
	{
		if (!isjumping && !isOnStair)
		{
			float floorLeft, floorTop, floorRight, floorBottom;
			float simonLeft, simonTop, simonRight, simonBottom;
			highFloor->GetBoundingBox(floorLeft, floorTop, floorRight, floorBottom);
			GetBoundingBox(simonLeft, simonTop, simonRight, simonBottom);
			if (simonRight < floorLeft || simonLeft > floorRight)
			{
				state = SIMON_STATE_IDLE;
				isJumpingFloor = true;
				vx = 0;
				vy = 0.95f;
				if (startJumpingFloor == 0)
					startJumpingFloor = GetTickCount();
			}
		}
	}
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_MOVE_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_AUTO_GOES:
		vx = SIMON_AUTO_SPEED_RIGHT;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_SITDOWN:
		vx = 0;
		break;
	case SIMON_STATE_JUMPING:
		OnGround = false;
		isjumping = true;
		vy = -SIMON_JUMP_SPEED_Y;
		y -= 5;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		isOnStair = false;
		checkRewind = false;
		isjumping = false;
		break;
	case SIMON_STATE_ATTACK_STAND:
		break;
	case SIMON_STATE_ATTACK_SITDOWN:
		vx = 0;
		break;
	case SIMON_STATE_ATTACK_STAND_SUBWEAPON:
	case SIMON_STATE_ATTACK_UP_STAIR_SUPWEAPON:
		vx = 0;
		break;
	case SIMON_STATE_CHANGECOLOR:
		changeColorId = -changeColorId;
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_GO_UP_STAIR:
		isOnStair = true;
		set_nx(originalStair->Get_nxStair());
		SetSpeed(originalStair->Get_nxStair()*SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		if (originalStair->Get_nyStair() < 0)
		{
			SetSpeed(-nx * SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		}
		break;
	case SIMON_STATE_GO_DOWN_STAIR:
		isOnStair = true;
		set_nx(originalStair->Get_nxStair());
		SetSpeed(originalStair->Get_nxStair()*(SIMON_STAIR_SPEED), SIMON_STAIR_SPEED);
		if (originalStair->Get_nyStair() > 0)
		{
			SetSpeed(-nx * SIMON_STAIR_SPEED, SIMON_STAIR_SPEED);
		}
		break;
	case SIMON_STATE_IDLE_UP_STAIR:
		SetSpeed(0, 0);
		isOnStair = true;
		break;
	case SIMON_STATE_WIN:
		vx = 0;
		isOnStair = false;
		checkRewind = false;
		isjumping = false;
	case SIMON_STATE_IDLE_DOWN_STAIR:
		SetSpeed(0, 0);
		isOnStair = true;
		break;
	case SIMON_STATE_ATTACK_UP_STAIR:
		isOnStair = true;
		SetSpeed(0, 0);
		set_nx(originalStair->Get_nxStair());
		checkRewind = true;
		currentAnimation = SIMON_ANI_ATTACK_UP_STAIR;
		break;
	case SIMON_STATE_ATTACK_DOWN_STAIR:
		checkRewind = true;
		isOnStair = true;
		SetSpeed(0, 0);
		set_nx(originalStair->Get_nxStair());
		currentAnimation = SIMON_ANI_ATTACK_DOWN_STAIR;
		break;
	case SIMON_STATE_DIE:
		vx = 0;
		isOnStair = false;
		checkRewind = false;
		currentAnimation = SIMON_ANI_DEAD;
		originalStair = nullptr;
		isjumping = false;
		break;
	case SIMON_STATE_HURT:
		if (untouchable_start == 0 && !isjumping && isOnGround() && !isOnStair)
		{
			isjumping = true;
			vy = -SIMON_HURT_SPEED_Y * 1.15;
			vx = -nx * SIMON_MOVE_SPEED* 1.25;
			y += 5;
			break;
		}
		checkRewind = true;
		animation_set->find(ani)->second->SetFinish(false);
		timeAtack = 0;
		break;
	}
}

void Simon::SetupAtacking()
{
	if (timeAtack)
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
	if (timeAtackSub && timeThrowWeapon == 0 && baseInfo->getHeart() > 0)
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
				timeThrowWeapon = GetTickCount();
			}
			baseInfo->setHeart(max(0, baseInfo->getHeart() - 1));
		}
	}
}

void Simon::RenderWeapon(LPANIMATION animation, Viewport * viewport)
{
	if (timeAtack > 0 && timeHurt ==0)
	{
		whip->updatePostision(animation->getCurrentFrame(), currentAnimation, flip);
		whip->draw(flip, viewport);
	}
}

void Simon::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (timeAtack)
	{
		whip->Update(dt, coObjects);

		if (timeAtack > 0 && GetTickCount() - timeAtack > 400)
		{
			Reset(currentAnimation);
			timeAtack = 0;
		}
	}

	if (timeAtackSub)
	{
		if (baseInfo->getIdSubWeapon() == ID_ENTITY_BOOMERANG_WEAPON)
		{
			baseInfo->getSubWeapon()->setLiveTime(GetTickCount());
		}
		if (timeAtackSub > 0 && GetTickCount() - timeAtackSub > 400)
		{
			Reset(currentAnimation);
			animation_set->find(currentAnimation)->second->SetFinish(false);
			timeAtackSub = 0;
		}
	}

	if (baseInfo->getIdSubWeapon() != ID_ENTITY_NULL)
	{
		if (GetTickCount() - timeThrowWeapon > 400 && timeThrowWeapon > 0 )
		{
			enableSubWeapon = false;
			timeThrowWeapon = 0;
			baseInfo->setIdSubWeapon(baseInfo->getIdSubWeapon());
		}
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 15;
	top = y + 3;
	right = x + width - 10;
	bottom = top + height - 3;

	if (state == Simon::SIMON_STATE_SITDOWN ||
		state == Simon::SIMON_STATE_ATTACK_SITDOWN)
	{
		left = x + 15;
		top = y + 15;
		right = x + width - 10;
		bottom = y + height;
	}
	else if (state == SIMON_STATE_JUMPING)
	{
		left = x + 15;
		top = y + 15;
		right = x + width - 10;
		bottom = y + height;
	}
}

void Simon::Render(Viewport* viewport)
{
	RenderBoundingBox(viewport);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		switch (state)
		{
		case SIMON_STATE_WALKING_RIGHT:
			currentAnimation = SIMON_ANI_WALKING;
			checkRewind = true;
			break;
		case SIMON_STATE_AUTO_GOES:
			currentAnimation = SIMON_ANI_WALKING_LOW;
			checkRewind = true;
			break;
		case SIMON_STATE_WALKING_LEFT:
			currentAnimation = SIMON_ANI_WALKING;
			checkRewind = true;
			break;
		case SIMON_STATE_SITDOWN:
			currentAnimation = SIMON_ANI_SITDOWN;
			checkRewind = false;
			break;
		case SIMON_STATE_JUMPING:
			if (vy < 0)
			{
				currentAnimation = SIMON_ANI_SITDOWN;
			}
			else if (vy == 0) currentAnimation = SIMON_ANI_IDLE;
			checkRewind = true;
			break;
		case SIMON_STATE_IDLE:
			currentAnimation = SIMON_ANI_IDLE;
			checkRewind = false;
			break;
		case SIMON_STATE_WIN:
			currentAnimation = SIMON_ANI_IDLE;
			checkRewind = false;
			break;
		case SIMON_STATE_ATTACK_STAND:
			checkRewind = true;
			currentAnimation = SIMON_ANI_ATTACK_STANDING;
			break;
		case SIMON_STATE_ATTACK_SITDOWN:
			checkRewind = true;
			currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
			break;
		case SIMON_STATE_ATTACK_STAND_SUBWEAPON:
			checkRewind = true;
			currentAnimation = SIMON_ANI_ATTACK_STANDING;
			break;
		case SIMON_STATE_CHANGECOLOR:
			checkRewind = true;
			if (changeColorId == -1)
			{
				currentAnimation = SIMON_ANI_COLOR;
			}
			else if (changeColorId == 1)
			{
				currentAnimation = SIMON_ANI_COLOR1;
			}
			break;
		case SIMON_STATE_GO_UP_STAIR:
			checkRewind = true;
			currentAnimation = SIMON_ANI_GO_UP_STAIR;
			break;
		case SIMON_STATE_GO_DOWN_STAIR:
			checkRewind = true;
			currentAnimation = SIMON_ANI_GO_DOWN_STAIR;
			break;
		case SIMON_STATE_IDLE_DOWN_STAIR:
			checkRewind = true;
			currentAnimation = SIMON_ANI_IDLE_GO_DOWN_STAIR;
			break;
		case SIMON_STATE_IDLE_UP_STAIR:
			checkRewind = true;
			currentAnimation = SIMON_ANI_IDLE_GO_UP_STAIR;
			break;
		case SIMON_STATE_ATTACK_UP_STAIR:
		case SIMON_STATE_ATTACK_UP_STAIR_SUPWEAPON:
			currentAnimation = SIMON_ANI_ATTACK_UP_STAIR;
			break;
		case SIMON_STATE_ATTACK_DOWN_STAIR:
			checkRewind = true;
			currentAnimation = SIMON_ANI_ATTACK_DOWN_STAIR;
			break;
		case SIMON_STATE_DIE:
			vx = 0;
			checkRewind = false;
			break;
		case SIMON_STATE_HURT:
			if (!isOnStair)
			{
				if (vy < 0)
				{
					currentAnimation = SIMON_ANI_HURT;
				}
				else 
				{
					SetState(SIMON_STATE_IDLE);
				}
				checkRewind = true;
				animation_set->find(ani)->second->SetFinish(false);
			}
			timeAtack = 0;
			break;
		}

	animation_set->find(currentAnimation)->second->SetLoop(checkRewind);

	LPANIMATION animation = animation_set->find(currentAnimation)->second;
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

bool Simon::isOnGround()
{
	return OnGround;
}

void Simon::Reset(int currentAnimation)
{
	switch (currentAnimation)
	{
	case SIMON_ANI_GO_UP_STAIR:
	case SIMON_ANI_ATTACK_UP_STAIR:
		SetState(SIMON_STATE_IDLE_UP_STAIR);
		break;
	case SIMON_ANI_IDLE_GO_UP_STAIR:
	case SIMON_ANI_IDLE_GO_DOWN_STAIR:
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

	if (!timeAtackSub)
	{
		whip->GetAnimationSet()->find(whip->getCurrentAnimation())->second->SetFinish(false);

	}
	animation_set->find(currentAnimation)->second->SetFinish(false);
}

void Simon::handleOutOfStair()
{
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
	if (originalStair->IsTwoDirection())
	{
		originalStair->Set_nyStair(0);
	}
	SetState(SIMON_STATE_IDLE);
}

void Simon::updateCollisionSubStair()
{
	if (isGoingAutoStair)
	{
		return;
	}
	if (isOnStair)
	{
		if (originalStair->Get_nyStair() > 0 && (y + height <= (originalStair->getPosition().y + originalStair->getHeight() - originalStair->GetHeightStair())
			|| y + height >= originalStair->getPosition().y + originalStair->getHeight())
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

	for (int i = 0; i < (int)(coObjects->size()); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_WALL
			|| coObjects->at(i)->getID() == ID_ENTITY_FLOOR ||
			(coObjects->at(i)->getID() == ID_ENTITY_BRICK && coObjects->at(i)->getName().compare("EdgeBrick")!=0)
			|| coObjects->at(i)->getID() == ID_ENTITY_MOVING_BRICK)
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
		else x += Dx;

		if (nx != 0) vx = 0;

		if (ny < 0 && !isOnStair)
		{
			vy = 0;
			isjumping = false;
			if (!OnGround) OnGround = true;
			if (isJumpingFloor)
			{
				isJumpingFloor = false;
				if (GetTickCount() - startJumpingFloor > 50 && startJumpingFloor > 0)
				{
					startJumpingSitFloor = GetTickCount();
					SetState(SIMON_STATE_SITDOWN);
				}
				startJumpingFloor = 0;
			}
			y += min_ty * dy + ny * 0.11f;
		}
		else y += Dy;
	}
	coEvents.clear();

	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

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
		case ID_ENTITY_FLOOR:
		{
			highFloor = dynamic_cast<Floor *>(coEvents[i]->obj);
		}
		break;
		case ID_ENTITY_PORTAL_POS_MAP:
		{
			PortalPosMap *ps = dynamic_cast<PortalPosMap *>(coEvents[i]->obj);
			if (ps->getName().compare("PortalEndMap")==0)
			{
				float wallLeft, wallTop, wallRight, wallBottom;
				float simonLeft, simonTop, simonRight, simonBottom;
				ps->GetBoundingBox(wallLeft, wallTop, wallRight, wallBottom);
				GetBoundingBox(simonLeft, simonTop, simonRight, simonBottom);
				Direct3DManager::getInstance()->getViewport()->setStartViewPortX(ps->GetStartViewportX());
				Direct3DManager::getInstance()->getViewport()->setEndViewPortX(ps->GetEndViewportX());
				ps->setID(ID_ENTITY_WALL);
				ps->SetPosition(D3DXVECTOR2(ps->GetStartViewportX(), ps->getPosition().y));
			}
			else 
			{
				Direct3DManager::getInstance()->getViewport()->setStartViewPortX(ps->GetStartViewportX());
				Direct3DManager::getInstance()->getViewport()->setEndViewPortX(ps->GetEndViewportX());
			}
		}
		break;
		case ID_ENTITY_BRICK:
		{
			if (isOnStair)
			{
				handleOutOfStair();
			}
			else
			{
				highFloor = dynamic_cast<CBrick *>(coEvents[i]->obj);
			}
		}
		break;
		case ID_ENTITY_ENTRANCE:
		{
			comeEntranceStart = GetTickCount();
			SetState(SIMON_STATE_AUTO_GOES);
		}
		break;
		case ID_ENTITY_MOVING_BRICK:
		{
			MovingBrick *movingBrick = dynamic_cast<MovingBrick *>(coEvents[i]->obj);
			SetSpeed(movingBrick->GetVx(), vy);
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
	case ID_ENTITY_CRYSTAL_BALL:
	case ID_ENTITY_VAMPIRE_BAT:
	case ID_ENTITY_DARK_BAT:
	case ID_ENTITY_SPEAR_KNIGHT:
	case ID_ENTITY_GHOST:
	case ID_ENTITY_FLEAMEN:
	case ID_ENTITY_WHITE_SKELETON:
	case ID_ENTITY_RAVEN:
		if (!untouchable && !isVisible && !isjumping)
		{
			SetState(SIMON_STATE_HURT);
			baseInfo->setHealth(max(0, baseInfo->getHealth() - 1));
			StartUntouchable();
		}
		break;
	case ID_ENTITY_WEAPON_REWARD:
		SetState(SIMON_STATE_CHANGECOLOR);
		if (timeChangeColor == 0)
		{
			timeChangeColor = GetTickCount();
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
		SetState(SIMON_STATE_WIN);
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
			originalStair = dynamic_cast<ObjectStair*>(coObjects->at(i));
		}
		break;
	case ID_ENTITY_ACTIVATEBOX:
	{
		ActivationBox *actionBox = dynamic_cast<ActivationBox *>(coObjects->at(i));
		actionBox->ActionObject(coObjects);
		if (actionBox->GetActivatedObjecId() != ID_ENTITY_VAMPIRE_BAT
			&& actionBox->GetActivatedObjecId() != ID_ENTITY_WHITE_SKELETON && 
			actionBox->GetActivatedObjecId() != ID_ENTITY_ZOMBIE)
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
		coObjects->at(i)->GetBoundingBox(l, t, r, b);
		rect1 = RECT{ long(l), long(t), long(r), long(b) };
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
	Direct3DManager::getInstance()->getViewport()->setStartViewPortX(getStartViewPort());
	Direct3DManager::getInstance()->getViewport()->setEndViewPortX(getEndViewPort());
	SetState(SIMON_STATE_IDLE);
	set_nx(1);
}

void Simon::setResetPosition(D3DXVECTOR2 pos)
{
	this->resetPosition = pos;
}

void Simon::AutoGoUpStair(State state)
{
	float sl, st, sr, sb;
	GetBoundingBox(sl, st, sr, sb);
	this->temporaryState = state;
	if ((int)sl > ((int)originalStair->getPosition().x - 10))
	{
		isGoingAutoStair = true;
		nx = -1;
		vx = nx * 0.04f;
		this->state = SIMON_STATE_AUTO_GOES;
	}
	else if ((int)sl < ((int)originalStair->getPosition().x + 10))
	{
		nx = 1;
		vx = nx * 0.04f;
		isGoingAutoStair = true;
		this->state = SIMON_STATE_AUTO_GOES;
	}
	else 
	{
		SetState(temporaryState);
	}
}

void Simon::UpdateGotoStair()
{
	float sl, st, sr, sb;
	GetBoundingBox(sl, st, sr, sb);
	if (originalStair && timeAutoGoStair == 0 && isGoingAutoStair && (int)sl == 
		((int)originalStair->getPosition().x - 10))
	{ 
		SetState(temporaryState);
		timeAutoGoStair = GetTickCount();
	}
}

void Simon::LoadWhip()
{
	whip = new Whip();
	whip->SetPosition(getPosition());
}

void Simon::UnloadWhip()
{
	if (whip != nullptr)
		delete whip;
}

Simon::~Simon()
{
}

