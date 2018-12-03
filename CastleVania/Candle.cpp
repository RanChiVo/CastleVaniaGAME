#include "Candle.h"


constexpr int CANDLE_ANI = 33;

Candle::Candle()
{
}

Candle::Candle(D3DXVECTOR2 position)
{
	id = ID_TEX_CANDLE;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_CANDLE)->Get("Candle1")->getRect();
	int height = r.bottom - r.top;

	x = position.x;
	y = position.y - height;

	LPANIMATION ani;

	ani = new Animation(150);
	ani->Add("Candle1");
	ani->Add("Candle2");
	Animations::GetInstance()->Add(CANDLE_ANI, ani);

	AddAnimation(CANDLE_ANI);

	currentAnimation = CANDLE_ANI;
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
}

void Candle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_CANDLE)->Get("Candle1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + height;
	bottom = y + width;
}

void Candle::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	Flip flip = normal;

	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

Candle::~Candle()
{
}
