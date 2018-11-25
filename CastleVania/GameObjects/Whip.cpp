#include "Whip.h"
#include "../ResourceManagement.h"
#include "BurnBarrel.h"
#include "Simon.h"


constexpr int WHIT_ANI_HIT_RIGHT1 = 16;
constexpr int WHIT_ANI_HIT_LEFT1 = 17;
constexpr int WHIT_ANI_HIT_RIGHT2 = 18;
constexpr int WHIT_ANI_HIT_LEFT2 = 19;
constexpr int WHIT_ANI_HIT_RIGHT3 = 20;
constexpr int WHIT_ANI_HIT_LEFT3 = 21;


Whip::Whip(D3DXVECTOR2 position)
{
	id = ID_TEX_WHIP;
	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add("1AttackRight1");
	ani->Add("1AttackRight2");
	ani->Add("1AttackRight3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT1, ani);

	ani = new Animation(200);
	ani->Add("1AttackLeft1");
	ani->Add("1AttackLeft2");
	ani->Add("1AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT1, ani);

	ani = new Animation(200);
	ani->Add("2AttackRight1");
	ani->Add("2AttackRight2");
	ani->Add("2AttackRight3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT2, ani);

	ani = new Animation(200);
	ani->Add("2AttackLeft1");
	ani->Add("2AttackLeft2");
	ani->Add("2AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT2, ani);

	ani = new Animation(200);
	ani->Add("3AttackRight1");
	ani->Add("3AttackRight2");
	ani->Add("3AttackRight3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT3, ani);

	ani = new Animation(200);
	ani->Add("3AttackLeft1");
	ani->Add("3AttackLeft2");
	ani->Add("3AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT3, ani);

	AddAnimation(WHIT_ANI_HIT_RIGHT1);
	AddAnimation(WHIT_ANI_HIT_LEFT1);

	AddAnimation(WHIT_ANI_HIT_RIGHT2);
	AddAnimation(WHIT_ANI_HIT_LEFT2);

	AddAnimation(WHIT_ANI_HIT_RIGHT3);
	AddAnimation(WHIT_ANI_HIT_LEFT3);

	state = WHIT_STATE_1;
	currentAnimation = WHIT_ANI_HIT_RIGHT1;
}

void Whip::updatePostision(int currentFrameSimon, int currentAni)
{

	if (currentAni == SIMON_ANI_ATTACK_STANDING_RIGHT)
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x - 10, y + 20));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x, y));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x + 57, y + 15));
			break;
		default:
			break;
		}
	else if (currentAni == SIMON_ANI_ATTACK_SITDOWN_RIGHT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x - 10, y + 30));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x + 5, y + 30));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x + 57, y + 20));
			break;
		default:
			break;
		}
	}
	else if (currentAni == SIMON_ANI_ATTACK_STANDING_LEFT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x + 60, y + 15));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x + 30, y));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x - 40, y + 13));
			break;
		default:
			break;
		}
	}
	else if (currentAni == SIMON_ANI_ATTACK_SITDOWN_LEFT)
	{
		switch (currentFrameSimon)
		{
		case 0:
			SetPosition(D3DXVECTOR2(x + 60, y + 28));
			break;
		case 1:
			SetPosition(D3DXVECTOR2(x + 15, y + 20));
			break;
		case 2:
			SetPosition(D3DXVECTOR2(x - 40, y + 20));
			break;
		default:
			break;
		}
	}
}

int Whip::getframe()
{
	return animations.find(currentAnimation)->second->getCurrentFrame();
}

int Whip::getCurrentAnimation()
{
	return currentAnimation;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
}

void Whip::Render(Viewport * viewport)
{

}

bool Whip::checkCollision(RECT A, RECT B)
{
	float left = B.left - A.right;
	float top = B.bottom - A.top;
	float right = B.right - A.left;
	float bottom = B.top - A.bottom;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

RECT Whip::getBounding()
{
	return this->bounding;
}

void Whip::draw(int direct, Viewport* viewport)
{
	if (state == WHIT_STATE_1)
	{
		if (direct == 1)
		{
			currentAnimation = WHIT_ANI_HIT_RIGHT1;
		}
		else currentAnimation = WHIT_ANI_HIT_LEFT1;
	}
	else if (state == WHIT_STATE_2)
	{
		if (direct == 1)
		{
			currentAnimation = WHIT_ANI_HIT_RIGHT2;
		}
		else currentAnimation = WHIT_ANI_HIT_LEFT2;
	}
	else if (state == WHIT_STATE_3)
	{
		if (direct == 1)
		{
			currentAnimation = WHIT_ANI_HIT_RIGHT3;
		}
		else currentAnimation = WHIT_ANI_HIT_LEFT3;
	}
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(pos.x, pos.y);

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	bounding = RECT{ int(l), int(t), int(r), int(b) };
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_WHIP)->Get("1AttackRight3")->getRect();
	float height = r.bottom - r.top;
	float width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

Whip::~Whip()
{
}
