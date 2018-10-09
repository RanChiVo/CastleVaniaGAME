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
	if (y > 100)		
	{	
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 480) x = 480;
	if (vx < 0 && x < 0) x = 0;
}

void Simon::loadResource()
{ 
	ResourceManagement *resourceHandle = ResourceManagement::GetInstance();
	resourceHandle->loadTexture(ID_TEX_SIMON, L"texture\\simon.png", D3DCOLOR_XRGB(255, 255, 255));
	//right
	resourceHandle->loadSprites(10001, 742, 2, 768, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10002, 796, 3, 828, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10003, 860, 1, 886, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10004, 918, 3, 952, 65, ID_TEX_SIMON);

	//left
	resourceHandle->loadSprites(10011, 195, 2, 221, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10012, 135, 3, 167, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10013, 77, 1, 103, 65, ID_TEX_SIMON);
	resourceHandle->loadSprites(10014, 11, 3, 45, 65, ID_TEX_SIMON);

	//jump right	
	resourceHandle->loadSprites(10021, 678, 0, 712, 48, ID_TEX_SIMON);

	//jump left
	resourceHandle->loadSprites(10022, 251, 0, 285, 48, ID_TEX_SIMON);

	Animations * animations = Animations::GetInstance();
	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new Animation(100);
	ani->Add(10011);
	animations->Add(401, ani);

	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(500, ani);

	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(501, ani);

	ani = new Animation(100);
	ani->Add(10022);
	animations->Add(601, ani);

	ani = new Animation(100);
	ani->Add(10021);
	animations->Add(600, ani);

	AddAnimation(400);		// idle right
	AddAnimation(401);		// idle left
	AddAnimation(500);		// walk right
	AddAnimation(501);		// walk left
	
	
	AddAnimation(600);
	AddAnimation(601);
	
	SetPosition(0.0f, 100.0f);
}

void Simon::Render()
{
	int ani;

	if (vx == 0)
	{
		if (nx>0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;
	else ani = SIMON_ANI_WALKING_LEFT;

	if (vy < 0)
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
		if (y==100)
			vy = -SIMON_JUMP_SPEED_Y;
		nx = 1;
		break;
	case SIMON_STATE_JUMPING_LEFT:
		if (y == 100)
			vy = -SIMON_JUMP_SPEED_Y;
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

