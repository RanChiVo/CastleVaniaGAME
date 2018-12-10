#include "Whip.h"
#include "../ResourceManagement.h"
#include "BurnBarrel.h"
#include "Simon.h"

Whip::Whip(D3DXVECTOR2 position)
{
	id = ID_TEX_WHIP;
	x = position.x;
	y = position.y;

	AddAnimation(TYPE1_WHIP);
	AddAnimation(TYPE2_WHIP);
	AddAnimation(TYPE3_WHIP);

	state = WHIT_STATE_1;
	currentAnimation = TYPE1_WHIP;
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

//bool Whip::checkCollision(RECT A, RECT B)
//{
//	float left = B.left - A.right;
//	float top = B.bottom - A.top;
//	float right = B.right - A.left;
//	float bottom = B.top - A.bottom;
//
//	if (left < 0 && right > 0 && top > 0 && bottom < 0)
//	{
//		return true;
//	}
//	return false;
//}

RECT Whip::getBounding()
{
	return this->bounding;
}

void Whip::draw(int direct, Viewport* viewport)
{
	if (state == WHIT_STATE_1)
	{
			currentAnimation = TYPE1_WHIP;
	}
	else if (state == WHIT_STATE_2)
	{
			currentAnimation = TYPE2_WHIP;
	}
	else if (state == WHIT_STATE_3)
	{
			currentAnimation = TYPE3_WHIP;
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
	RECT r;

	switch (state)
	{
	case WHIT_STATE_1:
		r = ResourceManagement::GetInstance()->getSprite(ID_TEX_WHIP)->Get("type1_whip_3")->getRect();
		break;
	case WHIT_STATE_2:
		r = ResourceManagement::GetInstance()->getSprite(ID_TEX_WHIP)->Get("type2_whip_3")->getRect();
		break;
	case WHIT_STATE_3:
		r = ResourceManagement::GetInstance()->getSprite(ID_TEX_WHIP)->Get("type3_whip_3")->getRect();
		break;
	}
	
	float height = r.bottom - r.top;
	float width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

Whip::~Whip()
{
}
