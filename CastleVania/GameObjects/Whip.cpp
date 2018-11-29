#include "Whip.h"
#include "../ResourceManagement.h"
#include "BurnBarrel.h"
#include "Simon.h"


constexpr int WHIT_ANI_HIT_1 = 16;
constexpr int WHIT_ANI_HIT_2 = 17;
constexpr int WHIT_ANI_HIT_3 = 18;


Whip::Whip(D3DXVECTOR2 position)
{
	id = ID_TEX_WHIP;
	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(200);
	ani->Add("1Attack1");
	ani->Add("1Attack2");
	ani->Add("1Attack3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_1, ani);

	ani = new Animation(200);
	ani->Add("2Attack1");
	ani->Add("2Attack2");
	ani->Add("2Attack3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_2, ani);

	ani = new Animation(200);
	ani->Add("3Attack1");
	ani->Add("3Attack2");
	ani->Add("3Attack3");

	Animations::GetInstance()->Add(WHIT_ANI_HIT_3, ani);

	AddAnimation(WHIT_ANI_HIT_1);
	AddAnimation(WHIT_ANI_HIT_2);
	AddAnimation(WHIT_ANI_HIT_3);

	state = WHIT_STATE_1;
	currentAnimation = WHIT_ANI_HIT_1;
}

void Whip::updatePostision(int currentFrameSimon, int currentAni, int direct)
{

	if (currentAni == SIMON_ANI_ATTACK_STANDING)
	{
		if (direct == 1)
		{
			switch (currentFrameSimon)
			{
			case 0:
				SetPosition(D3DXVECTOR2(x - 10, y + 18));
				break;
			case 1:
				SetPosition(D3DXVECTOR2(x, y + 5));
				break;
			case 2:
				SetPosition(D3DXVECTOR2(x + 57, y + 15));
				break;
			default:
				break;
			}
		}
		else 
		{
			switch (currentFrameSimon)
			{
			case 0:
				SetPosition(D3DXVECTOR2(x + 53, y + 20 ));
				break;
			case 1:
				SetPosition(D3DXVECTOR2(x + 30, y + 10));
				break;
			case 2:
				SetPosition(D3DXVECTOR2(x - 50, y + 15));
				break;
			default:
				break;
			}
		}
	}
	else if (currentAni == SIMON_ANI_ATTACK_SITDOWN)
	{
		if (direct == 1)
		{
			switch (currentFrameSimon)
			{
			case 0:
				SetPosition(D3DXVECTOR2(x - 10, y + 30));
				break;
			case 1:
				SetPosition(D3DXVECTOR2(x - 5, y + 30));
				break;
			case 2:
				SetPosition(D3DXVECTOR2(x + 57, y + 25));
				break;
			default:
				break;
			}
		}
		else
		{
			switch (currentFrameSimon)
			{
			case 0:
				SetPosition(D3DXVECTOR2(x + 57, y + 30));
				break;
			case 1:
				SetPosition(D3DXVECTOR2(x + 35, y + 30));
				break;
			case 2:
				SetPosition(D3DXVECTOR2(x - 50, y + 30));
				break;
			default:
				break;
			}
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
			currentAnimation = WHIT_ANI_HIT_1;
	}
	else if (state == WHIT_STATE_2)
	{
			currentAnimation = WHIT_ANI_HIT_2;
	}
	else if (state == WHIT_STATE_3)
	{
			currentAnimation = WHIT_ANI_HIT_3;
	}
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	Flip flip = flip_horiz;
	if (direct == 1)
	{
		flip = normal;
	}
	else flip = flip_horiz;

	animations.find(currentAnimation)->second->Render(pos.x, pos.y, flip);

	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	bounding = RECT{ int(l), int(t), int(r), int(b) };
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_WHIP)->Get("1Attack3")->getRect();
	float height = r.bottom - r.top;
	float width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

Whip::~Whip()
{
}
