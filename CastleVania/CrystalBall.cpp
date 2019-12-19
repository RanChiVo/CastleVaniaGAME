#include "CrystalBall.h"
#include "ResourceManagement.h"

constexpr DWORD SHOOT_TIME = 3000;

CrystalBall::CrystalBall(D3DXVECTOR2 pos, int nx)
{
	id = ID_ENTITY_CRYSTAL_BALL;
	state = STATE_SHOW;
	this->SetPosition(pos);
	this->nx = nx;
	AddAnimation(CRYSTAL_BALL_ANI);
	currentAnimation = CRYSTAL_BALL_ANI;
	width = Textures::GetInstance()->GetSizeObject(ID_ENTITY_CRYSTAL_BALL).first;
	height = Textures::GetInstance()->GetSizeObject(ID_ENTITY_CRYSTAL_BALL).second;
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
	//RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip;
	if (nx == 1) flip = normal;
	else flip = flip_horiz;
	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
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
