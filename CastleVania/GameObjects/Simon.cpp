#include "Simon.h"
#define ID_TEX_SIMON 0


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

	// simple screen edge collision!!!
	if (vx > 0 && x > 480) x = 480;
	if (vx < 0 && x < 0) x = 0;
}

void Simon::loadResource()
{
	ResourceManagement *resourceHandle = ResourceManagement::GetInstance();
	resourceHandle->loadTexture(ID_TEX_SIMON, L"Images\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//right
	resourceHandle->loadSprites(10001, 749, 2, 775, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10002, 803, 3, 835, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10003, 867, 1, 893, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10004, 925, 3, 959, 65, ID_TEX_SIMON);

	//left
	resourceHandle->loadSprites(10011, 195, 2, 221, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10012, 135, 3, 167, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10013, 77, 1, 103, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10014, 11, 3, 45, 65, ID_TEX_SIMON);

	//jump right	
	resourceHandle->loadSprites(10021, 685, 0, 719, 48, ID_TEX_SIMON);

	//jump left
	resourceHandle->loadSprites(10022, 251, 0, 285, 48, ID_TEX_SIMON);

	//sit down right
	resourceHandle->loadSprites(10031, 685, 0, 719, 48, ID_TEX_SIMON);

	//sit down left
	resourceHandle->loadSprites(10032, 251, 0, 285, 48, ID_TEX_SIMON);

	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;
	//idle right
	ani = new Animation(100);
	ani->Add(10004);
	animations->Add(400, ani);


	//idle left
	ani = new Animation(100);
	ani->Add(10014);
	animations->Add(401, ani);


	// walk right
	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(500, ani);


	// walk left
	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(501, ani);

	//jump right
	ani = new Animation(100);
	ani->Add(10021);
	animations->Add(600, ani);

	//jump left
	ani = new Animation(100);
	ani->Add(10022);
	animations->Add(601, ani);

	//sit down right
	ani = new Animation(100);
	ani->Add(10031);
	animations->Add(700, ani);

	//sit down left
	ani = new Animation(100);
	ani->Add(10032);
	animations->Add(701, ani);

	AddAnimation(400);		// idle right
	AddAnimation(401);		// idle left
	AddAnimation(500);		// walk right
	AddAnimation(501);		// walk left

	AddAnimation(600);		//jump right
	AddAnimation(601);		//jump left

	AddAnimation(700);		//sitdown right
	AddAnimation(701);		//sitdown left

	SetPosition(0.0f, 300.0f);
}

void Simon::Render()
{
	int ani;

	if (vx == 0)
	{
		if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;
	else ani = SIMON_ANI_WALKING_LEFT;

	if (vy == 0)
	{
		if (nx > 0) ani = SIMON_ANI_SIT_RIGHT;
		else ani = SIMON_ANI_SIT_LEFT;
	}
	else if (vy < 0)
	{
		if (nx > 0) ani = SIMON_ANI_JUMPING_RIGHT;
		else ani = SIMON_ANI_JUMPING_LEFT;
	}
	

	animations[ani]->Render(x, y);
}

void Simon::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_MOVE_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMPING_RIGHT:
		if (y == 300)
			vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_JUMPING_LEFT:
		if (y == 300)
			vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_SITDOWN_RIGHT:
		vy = 0;
		nx = 1;
		break;
	case SIMON_STATE_SITDOWN_LEFT:
		vy = 0;
		nx = -1;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;


	}
}

Simon::~Simon()
{
}

