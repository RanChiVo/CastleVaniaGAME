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

constexpr float SIMON_MOVE_SPEED = 0.12f;
constexpr int SIMON_JUMP_VEL = 350;
constexpr float SIMON_JUMP_SPEED_Y = 0.42f;
constexpr float SIMON_GRAVITY = 0.001f;
constexpr int SIMON_PROTECT_TIME = 2000;
constexpr float SIMON_STAIR_SPEED = 0.074f;
constexpr auto P0SITION_ENTRANCE = 1300;
constexpr int SIMON_UNTOUCHABLE_TIME = 5000;
constexpr int SIMON_ENTRANCE_TIME = 3000;

Simon::Simon()
{
	id = ID_ENTITY_SIMON;
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);
	level = 1;
	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE;
	WHIP_STATE = 1;
	levelWhip = 1;
	whip = new Whip();
	baseInfo = new BaseInfo();
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	UpdateWeapon(dt, coObjects);
	SetupAtacking();
	SetupSubWeapon(coObjects);
	handleState();

	if (level == 0)
	{
		if (GetTickCount() - comeEntranceStart <= SIMON_ENTRANCE_TIME)
			SetState(SIMON_STATE_WALKING_RIGHT);
		else if (comeEntranceStart > 0)
			comeEntranceStart = 0;
	}
	updateCollisionStair();
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
					SetState(SIMON_STATE_GO_UP_STAIR);
				}
			}
			else if (directInput->IsKeyDown(DIK_DOWN))
			{
				if (originalStair->get_ny() < 0)
				{
					SetState(SIMON_STATE_GO_DOWN_STAIR);
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
	}
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
			baseInfo->setHeart(baseInfo->getHeart() - 1);
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
}

void Simon::UpdateWeapon(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (attacking)
	{
		whip->Update(dt, coObjects);
		if (animations.find(currentAnimation)->second->getCurrentFrame() == 2 && whip->getframe() == 2)
		{
			animations.find(currentAnimation)->second->SetFinish(true);
			whip->animations.find(whip->getCurrentAnimation())->second->SetFinish(true);
		}
	}

	if (enableSubWeapon)
	{
		if (animations.find(currentAnimation)->second->getCurrentFrame() == 2)
		{
			animations.find(currentAnimation)->second->SetFinish(true);
		}
	}

	if (baseInfo->getIdSubWeapon() != ID_ENTITY_NULL)
	{
		if (GetTickCount() - startThrowWeapon > 500 && startThrowWeapon > 0)
		{
			enableSubWeapon = false;
			startThrowWeapon = 0;
		}
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width - 20;
	bottom = top + height;
}

void Simon::Render(Viewport* viewport)
{
	RenderBoundingBox(viewport);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	LPANIMATION animation = animations.find(currentAnimation)->second;

	if (animation)
	{
		if (nx == 1) flip = normal;
		else flip = flip_horiz;

		if (isOnStair)
		{
			if (state == SIMON_STATE_GO_DOWN_STAIR || state == SIMON_STATE_IDLE_DOWN_STAIR 
				|| state == SIMON_STATE_ATTACK_DOWN_STAIR)
			{
				if (nx > 0 && ny > 0)
				{
					flip = flip_horiz;
				}
				else if (nx < 0 && ny > 0)
				{
					flip = normal;
				}
			}
			else if (state == SIMON_STATE_GO_UP_STAIR || state == SIMON_STATE_IDLE_UP_STAIR
				|| state == SIMON_STATE_ATTACK_UP_STAIR)
			{
				if (nx < 0 && ny < 0)
				{
					flip = normal;
				}
				else if (nx > 0 && ny < 0)
				{
					flip = flip_horiz;
				}
			}
		}
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
		attacking = false;
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
		attacking = true;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_STANDING;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_ATTACK_JUMP_SUBWEAPON:
		enableSubWeapon = true;
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

	case SIMON_STATE_ATTACK_STAND_SUBWEAPON:
		vx = 0;
		enableSubWeapon = true;
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

	case SIMON_STATE_ATTACK_SITDOWN_SUBWEAPON:
		enableSubWeapon = true;
		vx = 0;
		checkRewind = false;
		currentAnimation = SIMON_ANI_ATTACK_SITDOWN;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		isOnStair = false;
		attacking = false;
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
		checkRewind = false;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		set_ny(originalStair->get_ny());
		SetSpeed(nx*SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		if (nx < 0 && ny < 0)
		{
			SetSpeed(SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		}
		else if (nx > 0 && ny < 0)
		{
			SetSpeed(-SIMON_STAIR_SPEED, -SIMON_STAIR_SPEED);
		}
		currentAnimation = SIMON_ANI_GO_UP_STAIR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_GO_DOWN_STAIR:
		checkRewind = false;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		set_ny(originalStair->get_ny());
		SetSpeed(nx*SIMON_STAIR_SPEED, SIMON_STAIR_SPEED);
		if (nx > 0 && ny > 0)
		{
			SetSpeed(-SIMON_STAIR_SPEED, SIMON_STAIR_SPEED);
		}
		else if (nx < 0 && ny > 0)
		{
			SetSpeed(SIMON_STAIR_SPEED, SIMON_STAIR_SPEED);
		}
		currentAnimation = SIMON_ANI_GO_DOWN_STAIR;
		Reset(currentAnimation);
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
		checkRewind = false;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		currentAnimation = SIMON_ANI_ATTACK_UP_STAIR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_ATTACK_DOWN_STAIR:
		attacking = true;
		checkRewind = false;
		isOnStair = true;
		set_nx(originalStair->get_nx());
		currentAnimation = SIMON_ANI_ATTACK_DOWN_STAIR;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_HURT:
		if (!isjumping)
		{
			isjumping = true;
			vy = -SIMON_JUMP_SPEED_Y;
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
			attacking = false;
		}
		checkRewind = false;
		break;
	}
	DebugOut(L"subweapon:{%d}\n", enableSubWeapon);
	animations.find(currentAnimation)->second->SetLoop(checkRewind);
}

void Simon::Reset(int currentAnimation)
{
	if (animations.find(currentAnimation)->second->IsFinished())
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
		animations.find(currentAnimation)->second->SetFinish(false);
	}

	if (whip->animations.find(whip->getCurrentAnimation())->second->IsFinished())
	{
		whip->animations.find(whip->getCurrentAnimation())->second->SetFinish(false);
	}
}

void Simon::updateCollisionStair()
{
	if (isOnStair)
	{
		if ((originalStair->get_ny() > 0 && (y <= (originalStair->getPosition().y - originalStair->getHeight()) || y + height >= originalStair->getPosition().y)) ||
			(originalStair->get_ny() < 0 && (y >= (originalStair->getPosition().y + originalStair->getHeight() - height) || y <= originalStair->getPosition().y)))
		{
			SetState(SIMON_STATE_IDLE);
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
			case ID_ENTITY_WALL:
				Dx = min_tx * dx + nx * 0.11f;
				if (nx != 0) vx = 0;
				break;
			case ID_ENTITY_ENTRANCE:
				comeEntranceStart = GetTickCount();
				break;
			case ID_ENTITY_WALL_ENTRANCE:
				if (coEvents[i]->obj->getName().compare("Spawn Zombie") == 0)
				{
					this->isInSpawn = true;
					idEnemySpawn = ID_ENTITY_ZOMBIE;
				}
				else if (coEvents[i]->obj->getName().compare("WallActivatePanther") == 0)
				{

				}
				else if (coEvents[i]->obj->getName().compare("Wall_behind_entrance") == 0)
				{
					level = 1;
					y = 291.00;
					x = 50;
					SetState(SIMON_STATE_IDLE);
				}
				else
				{
					Dx = min_tx * dx + nx * 0.11f;
					if (nx != 0) vx = 0;
				}
				break;
			case ID_ENTITY_FLOOR:
				if (coEvents[i]->obj->getName().compare("HighFloor") == 0)
				{
					if (ny < 0)
					{
						vy = 0;
						Dy = min_ty * dy + ny * 0.1f;
					}
				}
				else
				{
					if (ny != 0) vy = 0;
					Dy = min_ty * dy + ny * 0.1f;
				}
				break;
			case ID_ENTITY_ZOMBIE:
			case ID_ENTITY_PANTHER:
				SetState(SIMON_STATE_HURT);
				break;
			}
		}
		x += Dx;
		y += Dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::handleAfterCollision(vector <LPGAMEOBJECT>* coObjects, int id, int i, vector<LPCOLLISIONEVENT> *coEvents)
{
	switch (id)
	{
	case ID_ENTITY_ZOMBIE:
		SetState(SIMON_STATE_HURT);
		break;
	case ID_ENTITY_WALL_ENTRANCE:
		if (coObjects->at(i)->getName().compare("Spawn Zombie") == 0)
		{
			this->isInSpawn = true;
			idEnemySpawn = ID_ENTITY_ZOMBIE;
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
	case ID_ENTITY_FIRE_BOMB:
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
		TiledMap::CreateEffect();
		break;
	case ID_ENTITY_DAGGER:
		baseInfo->setIdSubWeapon(ID_ENTITY_DAGGER);
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
			originalStair = dynamic_cast<ObjectStair*>(coObjects->at(i));
		}
		break;
	case ID_ENTITY_PANTHER:
		Panther* panther = dynamic_cast<Panther*>(coObjects->at(i));
		panther->setActivate(true);
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		panther->setBBPlayer(D3DXVECTOR4(l, t, r, b));
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
		if (coObjects->at(i)->getID() == ID_ENTITY_PANTHER && coObjects->at(i)->GetState()!= 0)
		{
			Panther* panther = nullptr;
			panther = dynamic_cast<Panther*>(coObjects->at(i));
			if (nx > 0)
			{
				rect1 = panther->getBBActivateRight();
			}
			else if (nx < 0)
			{
				rect1 =  panther->getBBActivateLeft();
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

