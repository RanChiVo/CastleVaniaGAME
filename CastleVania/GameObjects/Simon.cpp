#include "Simon.h"
constexpr int  ID_TEX_SIMON = 0;

Simon::Simon()
{
}

void Simon::Update(DWORD dt)
{
	GameObject::Update(dt);

	// simple JUMP
	vy += SIMON_GRAVITY;
	if (y > 300)
	{
		vy = 0; y = 300.0f;
	}
	// simple ScreenBase edge collision!!!
	if (vx > 0 && x > 480) x = 480;
	if (vx < 0 && x < 0) x = 0;
}

void Simon::loadResource()
{
	resourceManagement->loadTexture(ID_TEX_SIMON, L"Resources\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//right
	resourceManagement->loadSprites(10001, 749, 2, 775, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites(10002, 803, 3, 835, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites(10003, 867, 1, 893, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites(10004, 925, 3, 959, 65, ID_TEX_SIMON);

	//left
	resourceManagement->loadSprites(10011, 195, 2, 221, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites(10012, 135, 3, 167, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites(10013, 77, 1, 103, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites(10014, 11, 3, 45, 65, ID_TEX_SIMON);

	//jump right	
	resourceManagement->loadSprites(10021, 685, 0, 719, 48, ID_TEX_SIMON);

	//jump left
	resourceManagement->loadSprites(10022, 251, 0, 285, 48, ID_TEX_SIMON);

	//sit down right
	resourceManagement->loadSprites(10031, 685, -15, 719, 48, ID_TEX_SIMON);

	//sit down left
	resourceManagement->loadSprites(10032, 251, -15, 285, 48, ID_TEX_SIMON);

	//facing backward
	resourceManagement->loadSprites(10040, 857, 65, 891, 131, ID_TEX_SIMON);

	LPANIMATION ani;
	//idle right
	ani = new Animation(100);
	ani->Add(10004);
	resourceManagement->Getanimations->Add(400, ani);

	//idle left
	ani = new Animation(100);
	ani->Add(10014);
	resourceManagement->Getanimations->Add(401, ani);

	// walk right
	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	resourceManagement->Getanimations->Add(500, ani);

	// walk left
	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	resourceManagement->Getanimations->Add(501, ani);

	//jump right
	ani = new Animation(100);
	ani->Add(10021);
	resourceManagement->Getanimations->Add(600, ani);

	//jump left
	ani = new Animation(100);
	ani->Add(10022);
	resourceManagement->Getanimations->Add(601, ani);

	//sit down right
	ani = new Animation(100);
	ani->Add(10031);
	resourceManagement->Getanimations->Add(700, ani);

	//sit down left
	ani = new Animation(100);
	ani->Add(10032);
	resourceManagement->Getanimations->Add(701, ani);

	//facing backward
	ani = new Animation(100);
	ani->Add(10040);
	resourceManagement->Getanimations->Add(800, ani);

	AddAnimation(400);		// idle right
	AddAnimation(401);		// idle left
	AddAnimation(500);		// walk right
	AddAnimation(501);		// walk left

	AddAnimation(600);		//jump right
	AddAnimation(601);		//jump left

	AddAnimation(700);		//sitdown right
	AddAnimation(701);		//sitdown left

	AddAnimation(800);		//facing backward

	SetPosition(0.0f, 300.0f);
}

void Simon::Render()
{
	int ani;
	if (vx == 0)
	{
		if (isSitdown == 0)
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
		else
		{
			if (nx > 0) ani = SIMON_ANI_SITDOWN_RIGHT;
			else ani = SIMON_ANI_SITDOWN_LEFT;
		}
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;
	else ani = SIMON_ANI_WALKING_LEFT;

	if (vy < 0)
	{
		if (nx > 0) ani = SIMON_ANI_JUMPING_RIGHT;
		else ani = SIMON_ANI_JUMPING_LEFT;
	}

	GameObject::animations[ani]->Render(x, y);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		isSitdown = 0;
		vx = SIMON_MOVE_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		isSitdown = 0;
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMPING_RIGHT:
		if (y == 300)
			vy = -SIMON_JUMP_SPEED_Y;
		isSitdown = 0;
		break;
	case SIMON_STATE_JUMPING_LEFT:
		if (y == 300)
			vy = -SIMON_JUMP_SPEED_Y;
		isSitdown = 0;
		break;
	case SIMON_STATE_SITDOWN_RIGHT:
		isSitdown = 1;
		vx = 0;
		nx = 1;
		break;
	case SIMON_STATE_SITDOWN_LEFT:
		isSitdown = 1;
		vx = 0;
		nx =-1;
		break;
	case SIMON_STATE_IDLE:
		isSitdown = 0;
		vx = 0;
		break;
	}
}

Simon::~Simon()
{
}
