#include "Door.h"
#include "../CastleVania/Direct3DManager.h"
#include "../CastleVania/GameObjects/Simon.h"

constexpr int DOOR_ACTION_1_TIME = 2400;
constexpr int DOOR_ACTION_2_TIME = 450;
constexpr int DOOR_ACTION_3_TIME = 1000;
constexpr int DOOR_ACTION_4_TIME = 460;
constexpr int DOOR_ACTION_5_TIME = 2660;

DWORD Door::action1Start;
DWORD Door::action2Start;
DWORD Door::action3Start;
DWORD Door::action4Start;
DWORD Door::action5Start;

Door::Door(D3DXVECTOR2 position)
{
	action1Start = 0;
	action2Start = 0;
	action3Start = 0;
	action4Start = 0;
	action5Start = 0;

	id = ID_ENTITY_DOOR;
	SetPosition(position);
	state = DOOR_STATE_CLOSE;
	//AddAnimation(OPEN_ANI);
	//AddAnimation(CLOSE_ANI);
	//AddAnimation(OPENING_ANI);
	//AddAnimation(CLOSING_ANI);
	currentAnimation = CLOSE_ANI;
}

void Door::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	handleState();
	if (action1Start > 0)
	{
		if (GetTickCount() - action1Start > DOOR_ACTION_1_TIME)
		{
			action1Start = 0;
			action2Start = GetTickCount();
		}
		else
		{
			Direct3DManager::getInstance()->getViewport()->autoMove(dt);
			Direct3DManager::getInstance()->getViewport()
				->setState(Direct3DManager::getInstance()->getViewport()->STATE_LOCK);
			Simon::getInstance()->setIsMovingDoor(true);
		}
	}
	if (action2Start > 0)
	{
		if (GetTickCount() - action2Start > DOOR_ACTION_2_TIME)
		{
			action2Start = 0;
			action3Start = GetTickCount();
		}
		else
		{
			state = DOOR_STATE_OPENING;
		}
	}
	if (action3Start > 0)
	{
		if (GetTickCount() - action3Start > DOOR_ACTION_3_TIME)
		{
			action3Start = 0;
			action4Start = GetTickCount();
		}
		else
		{
			state = DOOR_STATE_OPEN;
			Simon::getInstance()->moveRight(dt);
		}
	}
	if (action4Start > 0)
	{
		if (GetTickCount() - action4Start > DOOR_ACTION_4_TIME)
		{
			action4Start = 0;
			action5Start = GetTickCount();
		}
		else
		{
			Simon::getInstance()->SetState(Simon::getInstance()->SIMON_STATE_IDLE);
			state = DOOR_STATE_CLOSING;
		}
	}
	if (action5Start > 0)
	{
		if (GetTickCount() - action5Start > DOOR_ACTION_5_TIME)
		{
			action5Start = 0;
			Direct3DManager::getInstance()->getViewport()->setState(Direct3DManager::getInstance()->getViewport()->STATE_ACTION);
			name = "Wall";
			id = ID_ENTITY_WALL_ENTRANCE;
			Direct3DManager::getInstance()->getViewport()->setStartViewPortX(Direct3DManager::getInstance()->getViewport()->getX());
			Direct3DManager::getInstance()->getViewport()->setEndViewPortX(512);
			Simon::getInstance()->setIsMovingDoor(false);
		}
		else
		{
			state = DOOR_STATE_CLOSE;
			Direct3DManager::getInstance()->getViewport()->autoMove(dt);
		}
	}
}

void Door::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
}

void Door::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state==DOOR_STATE_CLOSE)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
	else
	{
		left = top = right = bottom = 0;
	}
}

void Door::startAction()
{
	if (action1Start > 0 || action2Start > 0 || action3Start > 0 || action4Start > 0 || action5Start > 0)
		return;
	action1Start = GetTickCount();
}

void Door::handleState()
{
	switch (state)
	{
	case DOOR_STATE_CLOSE:
		currentAnimation = CLOSE_ANI;
		break;
	case DOOR_STATE_OPEN:
		currentAnimation = OPEN_ANI;
		break;
	case DOOR_STATE_CLOSING:
		currentAnimation = CLOSING_ANI;
		break;
	case DOOR_STATE_OPENING:
		currentAnimation = OPENING_ANI;
		break;
	}
}

Door::~Door()
{
}
