#include "Whip.h"
#include "../ResourceManagement.h"


Whip::Whip()
{
	
}

void Whip::Innitialize()
{
	SetStateWhip(WHIP_HIT_STAND);
}

void Whip::loadResource()
{
	ResourceManagement*resourceManagement = ResourceManagement::GetInstance();
	resourceManagement->loadResource();

	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add("AttackRight1");
	ani->Add("AttackRight2");
	ani->Add("AttackRight3");

	resourceManagement->Getanimations->Add(100, ani);

	GameObject::SetPosition(0.0f, 260);
}

void Whip::handleState()
{

	switch (state)
	{
	case WHIP_HIT_STAND:

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		checkRewind = true;
		break;
		case SIMON_STAT
}

void Whip::Update(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y - 15;
}

void Whip::SetStateWhip(int state)
{
	this->state = state;
}





Whip::~Whip()
{
}
