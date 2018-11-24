#include "MiraculousBag.h"
#include "../ResourceManagement.h"

constexpr int  MIRACULOUSBAG_ANI_HIDE = 27;
constexpr int  MIRACULOUSBAG_ANI_SHOW = 28;
constexpr float MIRACULOUSBAG_GRAVITY = 0.002f;

MiraculousBag::MiraculousBag()
{
}

MiraculousBag::MiraculousBag(D3DXVECTOR2 position)
{
	id = ID_TEX_MIRACULOUS_BAG;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_MIRACULOUS_BAG)->Get("miraculous_bag1")->getRect();

	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(150);
	ani->Add("miraculous_bag1");
	Animations::GetInstance()->Add(MIRACULOUSBAG_ANI_HIDE, ani);

	ani = new Animation(150);
	ani->Add("miraculous_bag1");
	ani->Add("miraculous_bag2");
	ani->Add("miraculous_bag3");

	Animations::GetInstance()->Add(MIRACULOUSBAG_ANI_SHOW, ani);

	AddAnimation(MIRACULOUSBAG_ANI_HIDE);
	AddAnimation(MIRACULOUSBAG_ANI_SHOW);

	state = MIRACULOUSBAG_STATE_HIDE;
	currentAnimation = MIRACULOUSBAG_ANI_HIDE;
}

void MiraculousBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == MIRACULOUSBAG_STATE_HIDE)
	{
		currentAnimation = MIRACULOUSBAG_ANI_HIDE;
	}
	else if (state = MIRACULOUSBAG_STATE_SHOW)
	{
		currentAnimation = MIRACULOUSBAG_ANI_SHOW;

		if (animations.find(currentAnimation)->second->getCurrentFrame() == 3)

			animations.find(currentAnimation)->second->SetFinish1(true);
	}
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
	animations.find(currentAnimation)->second->SetLoop(true);
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	animations.find(currentAnimation)->second->Render(position.x, position.y);
}


MiraculousBag::~MiraculousBag()
{
}
