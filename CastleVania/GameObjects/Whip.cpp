#include "Whip.h"
#include "../ResourceManagement.h"
#include "BurnBarrel.h"
#include "Simon.h"

Whip::Whip()
{
	id = ID_ENTITY_WHIP;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	AddAnimation(TYPE1_WHIP);
	AddAnimation(TYPE2_WHIP);
	AddAnimation(TYPE3_WHIP);

	state = WHIT_STATE_1;
	currentAnimation = TYPE1_WHIP;
	bbLevel1 = ResourceManagement::GetInstance()->getSprite(ID_ENTITY_WHIP)->Get("type1_whip_3")->getRect();
	bbLevel2 = ResourceManagement::GetInstance()->getSprite(ID_ENTITY_WHIP)->Get("type2_whip_3")->getRect();
	bbLevel3 = ResourceManagement::GetInstance()->getSprite(ID_ENTITY_WHIP)->Get("type3_whip_3")->getRect();
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

RECT Whip::getBounding()
{
	return this->bounding;
}

void Whip::Render(Viewport * viewport)
{
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

	//RenderBoundingBox(viewport);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (animations.find(currentAnimation)->second->getCurrentFrame() == 2)
	{
		left = x;
		top = y;
		RECT r;

		switch (state)
		{
		case WHIT_STATE_1:
			r = bbLevel1;
			break;
		case WHIT_STATE_2:
			r = bbLevel2;
			break;
		case WHIT_STATE_3:
			r = bbLevel3;
			break;
		}

		float height = float(r.bottom - r.top);
		float width = float(r.right - r.left);
		right = x + width;
		bottom = y + height;
	}
	else return;
}

Whip::~Whip()
{
}
