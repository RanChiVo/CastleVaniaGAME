#include "Whip.h"
#include "../ResourceManagement.h"
#include "Simon.h"
#include "BurnBarrel.h"

constexpr int WHIT_ANI_HIT_RIGHT = 14;
constexpr int WHIT_ANI_HIT_LEFT = 15;

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

	Animations::GetInstance()->Add(WHIT_ANI_HIT_RIGHT, ani);

	ani = new Animation(200);
	ani->Add("1AttackLeft1");
	ani->Add("1AttackLeft2");
	ani->Add("1AttackLeft3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_LEFT, ani);

	AddAnimation(WHIT_ANI_HIT_RIGHT);
	AddAnimation(WHIT_ANI_HIT_LEFT);

	currentAnimation = WHIT_ANI_HIT_RIGHT;
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

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* ObjectList, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, ObjectList);
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
	if (direct == 1)
	{
		currentAnimation = WHIT_ANI_HIT_RIGHT;
	}
	else currentAnimation = WHIT_ANI_HIT_LEFT;

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
