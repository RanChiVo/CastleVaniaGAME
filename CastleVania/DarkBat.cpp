#include "DarkBat.h"
#include "GameObjects/Simon.h"
#include "Direct3DManager.h"
#include "BallDarkBat.h"

constexpr DWORD  DARK_BAT_TIME_RANDOM_MOVE = 1200;
constexpr DWORD  DARK_BAT_TIME_IDLE = 1500;
constexpr DWORD  DARK_BAT_TIME_FLY_ACTACK = 1200;
constexpr DWORD  DARK_BAT_TIME_HURT = 600;
constexpr DWORD  DARK_BAT_TIME_EFFECT = 1600;
constexpr int  DARK_BAT_MAX_DISTANCE_RANDOM = 216;

bool DarkBat::isActivate = false;
DWORD DarkBat::startTimeHurt = 0;
BaseInfo DarkBat::baseInfo = BaseInfo();

DarkBat::DarkBat(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_DARK_BAT;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	originalLocation = pos;
	activatePositionMaxX = 512;
	SetState(DARK_BAT_STATE_IDLE);
	baseInfo.setHealth(1);
}

void DarkBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state != DARK_BAT_STATE_EFFECT_DESTROY)
	{
		left = x;
		top = y;
		right = left + width;
		bottom = top + height;
	}
	else left = top = right = bottom = 0;
}

void DarkBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	x += dx;
	y += dy;

	changeActivateToMoveRandom();
	changeMoveRandomToIdle();
	changeIdleRandomToAtack();
	changeAtackToMoveRandom();

	if (Simon::getInstance()->GetState() == Simon::SIMON_STATE_DIE)
	{
		SetState(DARK_BAT_STATE_IDLE);
		baseInfo.setHealth(16);
		SetPosition(originalLocation);
		hasBeenActivate = false;
		isActivate = false;
	}

	if (startTimeHurt > 0 && GetTickCount() - startTimeHurt > DARK_BAT_TIME_HURT)
	{
		startTimeHurt = 0;
		baseInfo.setHealth(max(0, baseInfo.getHealth() - 1));
	}

	if (baseInfo.getHealth() <= 0 && state != DARK_BAT_STATE_EFFECT_DESTROY)
	{
		vx = vy = 0;
		SetState(DARK_BAT_STATE_EFFECT_DESTROY);
		startTimeEffect = GetTickCount();
	}

	if (startTimeEffect > 0 && GetTickCount() - startTimeEffect > DARK_BAT_TIME_EFFECT)
	{
		startTimeEffect = 0;
		SetState(STATE_DETROY);
		Simon::getInstance()->getBaseInfo()
			->setScore(Simon::getInstance()->getBaseInfo()->getScore() + 3000);
		BallDarkBat* ballDarkBat = new BallDarkBat(D3DXVECTOR2(originalLocation.x + width / 3, originalLocation.y + height / 3));
		coObjects->push_back(ballDarkBat);
	}

	Enemy::Update(dt, coObjects);
}

void DarkBat::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == -1) flip = normal;
	else flip = flip_horiz;
	AnimationSets * animation_sets = AnimationSets::GetInstance();

	if (state == DARK_BAT_STATE_EFFECT_DESTROY)
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_EFFECT);
		SetAnimationSet(ani_set);
	}
	else
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_DARK_BAT);
		SetAnimationSet(ani_set);
	}
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);

	if (startTimeHurt > 0)
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_EFFECT);
		ani_set->find(ANI_EFFECT_STAR)->second->Render(position.x + width / 3, position.y + height / 3, flip);
	}

	Enemy::Render(viewport);
}

void DarkBat::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case DARK_BAT_STATE_MOVERANDOM:
		currentAnimation = DARK_BAT_FLY_ANI;
		break;
	case DARK_BAT_STATE_IDLE:
		vx = 0;
		vy = 0;
		currentAnimation = DARK_BAT_IDLE_ANI;
		break;
	case DARK_BAT_STATE_EFFECT_DESTROY:
		currentAnimation = ANI_EFFECT_FIRE_DARK_BAT;
		break;
	}
}

void DarkBat::changeActivateToMoveRandom()
{
	if (!hasBeenActivate && isActivate)
	{
		SetState(DARK_BAT_STATE_MOVERANDOM);
		startTimeMoveRandom = GetTickCount();
		handleMoveRandom();
		hasBeenActivate = true;
	}
}

void DarkBat::changeMoveRandomToIdle()
{
	if (startTimeMoveRandom > 0 && GetTickCount() - startTimeMoveRandom > DARK_BAT_TIME_RANDOM_MOVE)
	{
		vx = vy = 0;
		startTimeIdle = GetTickCount();
		startTimeMoveRandom = 0;
	}
}

void DarkBat::changeIdleRandomToAtack()
{
	if (startTimeIdle > 0 && GetTickCount() - startTimeIdle > DARK_BAT_TIME_IDLE)
	{
		startTimeIdle = 0;
		startTimeActackPlayer = GetTickCount();
		vx = (Simon::getInstance()->getPosition().x - x) / DARK_BAT_TIME_FLY_ACTACK;
		vy = (Simon::getInstance()->getPosition().y - y) / DARK_BAT_TIME_FLY_ACTACK;
	}
}

void DarkBat::changeAtackToMoveRandom()
{
	if (startTimeActackPlayer > 0 && GetTickCount() - startTimeActackPlayer > DARK_BAT_TIME_RANDOM_MOVE)
	{
		startTimeActackPlayer = 0;
		startTimeMoveRandom = GetTickCount();
		handleMoveRandom();
	}
}

void DarkBat::handleMoveRandom()
{
	int activateAreaX = activatePositionMaxX - Direct3DManager::getInstance()->getViewport()->getStartViewportX();
	int randomPositionX = rand() % (activateAreaX)+Direct3DManager::getInstance()->getViewport()->getStartViewportX();
	int activateAreaY = DARK_BAT_MAX_DISTANCE_RANDOM - originalLocation.y;
	int randomPositionY = rand() % (activateAreaY)+ originalLocation.y;
	vx = (randomPositionX - x) / DARK_BAT_TIME_RANDOM_MOVE;
	vy = (randomPositionY - y) / DARK_BAT_TIME_RANDOM_MOVE;
}

DarkBat::~DarkBat()
{
}
