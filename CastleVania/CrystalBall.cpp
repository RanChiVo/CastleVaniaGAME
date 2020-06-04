#include "CrystalBall.h"

constexpr DWORD SHOOT_TIME = 3000;

CrystalBall::CrystalBall(D3DXVECTOR2 pos, int nx)
{
	id = ID_ENTITY_CRYSTAL_BALL;
	state = STATE_SHOW;
	this->SetPosition(pos);
	this->nx = nx;
	currentAnimation = CRYSTAL_BALL_ANI;
	AnimationSets * animation_sets = AnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(id);
	SetAnimationSet(ani_set);
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	vx = nx * 0.07f;
	timeShoot = 0;
}

void CrystalBall::startShoot()
{
	if (timeShoot == 0)
	{
		timeShoot = GetTickCount();
	}
}

void CrystalBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	if (GetTickCount() - timeShoot > SHOOT_TIME && timeShoot)
	{
		state = STATE_DETROY;
		timeShoot = 0;
	}

	if (!checkInsideViewPort(Direct3DManager::getInstance()->getViewport()))
	{
		state = STATE_DETROY;
	}
}

void CrystalBall::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	animation_set->at(currentAnimation)->Render(position.x, position.y, flip);
}

void CrystalBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + this->width;
	bottom = y + this->height;
}

CrystalBall::~CrystalBall()
{
}
