#include "MiraculousBag.h"
#include "../ResourceManagement.h"

constexpr float MIRACULOUSBAG_GRAVITY = 0.0001f;


MiraculousBag::MiraculousBag()
{
}

MiraculousBag::MiraculousBag(D3DXVECTOR2 position)
{
	id = ID_TEX_MIRACULOUS_BAG;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_MIRACULOUS_BAG)->Get("miraculous_bag1")->getRect();

	x = position.x;
	y = position.y;


	AddAnimation(MIRACULOUSBAG_ANI);

	state = MIRACULOUSBAG_STATE_HIDE;
	currentAnimation = MIRACULOUSBAG_ANI;
}

void MiraculousBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);
}

void MiraculousBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_MIRACULOUS_BAG)->Get("miraculous_bag1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void MiraculousBag::Render(Viewport * viewport)
{
	if (state == MIRACULOUSBAG_STATE_SHOW)
	{
		animations.find(currentAnimation)->second->SetLoop(true);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
		RenderBoundingBox(viewport);
	}
	else return;
}


MiraculousBag::~MiraculousBag()
{
}
