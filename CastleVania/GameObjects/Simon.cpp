#include "Simon.h"
constexpr int  ID_TEX_SIMON = 0;
constexpr auto GROUND_POSITION = 300;

Simon::Simon()
{
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);

	SetState(SIMON_STATE_IDLE);
	ani = SIMON_ANI_IDLE_RIGHT;
}

void Simon::Update(DWORD dt)
{
	GameObject::Update(dt);

	// simple JUMP
	vy += SIMON_GRAVITY;
	if (y > GROUND_POSITION)
	{
		vy = 0; y = GROUND_POSITION;
	}
	// simple ScreenBase edge collision!!!
	if (vx > 0 && x > 480) x = 480;
	if (vx < 0 && x < 0) x = 0;

	handleState();
	if (jumped)
	{
		SetState(SIMON_STATE_IDLE);
		jumped = false;
	}
}

void Simon::loadResource()
{
	ResourceManagement*resourceManagement = ResourceManagement::GetInstance();
	resourceManagement->loadTexture(ID_TEX_SIMON, L"Resources\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//right
	resourceManagement->loadSprites("WalkingRight1", 749, 2, 775, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("WalkingRight2", 803, 3, 835, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("WalkingRight3", 867, 1, 893, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("WalkingRight4", 925, 3, 959, 65, ID_TEX_SIMON);

	//left
	resourceManagement->loadSprites("WalkingLeft1", 195, 2, 221, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("WalkingLeft2", 135, 3, 167, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("WalkingLeft3", 77, 1, 103, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("WalkingLeft4", 11, 3, 45, 65, ID_TEX_SIMON);

	//jump right	
	resourceManagement->loadSprites("JumpRight", 685, 0, 719, 48, ID_TEX_SIMON);

	//jump left
	resourceManagement->loadSprites("JumpLeft", 251, 0, 285, 48, ID_TEX_SIMON);

	//sit down right
	resourceManagement->loadSprites("SitdownRight", 685, -15, 719, 48, ID_TEX_SIMON);

	//sit down left
	resourceManagement->loadSprites("SitdownLeft", 251, -15, 285, 48, ID_TEX_SIMON);

	//facing backward
	//resourceManagement->loadSprites(10040, 857, 65, 891, 131, ID_TEX_SIMON);

	//attack standing right
	resourceManagement->loadSprites("AttackStandRight1", 490, 3, 550, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackStandRight2", 550, 3, 610, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackStandRight3", 610, 3, 670, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackStandRight3", 610, 3, 670, 65, ID_TEX_SIMON);

	//attack standing left
	resourceManagement->loadSprites("AttackStandLeft1", 420, 3, 480, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackStandLeft2", 360, 3, 420, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackStandLeft3", 300, 3, 360, 65, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackStandLeft3", 300, 3, 360, 65, ID_TEX_SIMON);

	//attack Sitdown right
	resourceManagement->loadSprites("AttackSitdownRight1", 60, 134, 121, 180, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackSitdownRight2", 0, 132, 75, 180, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackSitdownRight3", 421, 66, 481, 114, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackSitdownRight3", 421, 66, 481, 114, ID_TEX_SIMON);

	//attack Sitdown left
	resourceManagement->loadSprites("AttackSitdownLeft1", 849, 134, 910, 180, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackSitdownLeft2", 911, 132, 970, 180, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackSitdownLeft3", 489, 66, 549, 114, ID_TEX_SIMON);
	resourceManagement->loadSprites("AttackSitdownLeft3", 489, 66, 549, 114, ID_TEX_SIMON);

	LPANIMATION ani;
	//idle right
	ani = new Animation(100);
	ani->Add("WalkingRight4");
	resourceManagement->Getanimations->Add(400, ani);

	//idle left
	ani = new Animation(100);
	ani->Add("WalkingLeft4");
	resourceManagement->Getanimations->Add(401, ani);

	// walk right
	ani = new Animation(100);
	ani->Add("WalkingRight1");
	ani->Add("WalkingRight2");
	ani->Add("WalkingRight3");
	ani->Add("WalkingRight4");
	resourceManagement->Getanimations->Add(500, ani);

	// walk left
	ani = new Animation(100);

	ani->Add("WalkingLeft1");
	ani->Add("WalkingLeft2");
	ani->Add("WalkingLeft3");
	ani->Add("WalkingLeft4");
	resourceManagement->Getanimations->Add(501, ani);

	//jump right
	ani = new Animation(100);
	ani->Add("JumpRight");
	resourceManagement->Getanimations->Add(600, ani);

	//jump left
	ani = new Animation(100);
	ani->Add("JumpLeft");
	resourceManagement->Getanimations->Add(601, ani);

	//sit down right
	ani = new Animation(100);
	ani->Add("SitdownRight");
	resourceManagement->Getanimations->Add(700, ani);

	//sit down left
	ani = new Animation(100);
	ani->Add("SitdownLeft");
	resourceManagement->Getanimations->Add(701, ani);

	//facing backward
	/*ani = new Animation(100);
	ani->Add(10040);
	resourceManagement->Getanimations->Add(800, ani);
*/
	//attack standing right
	ani = new Animation(100);
	ani->Add("AttackStandRight1");
	ani->Add("AttackStandRight2");
	ani->Add("AttackStandRight3");
	ani->Add("AttackStandRight3");
	resourceManagement->Getanimations->Add(900, ani);

	//attack standing left
	ani = new Animation(100);
	ani->Add("AttackStandLeft1");
	ani->Add("AttackStandLeft2");
	ani->Add("AttackStandLeft3");
	ani->Add("AttackStandLeft3");
	resourceManagement->Getanimations->Add(901, ani);

	//attack Sitdown right
	ani = new Animation(100);
	ani->Add("AttackSitdownRight1");
	ani->Add("AttackSitdownRight2");
	ani->Add("AttackSitdownRight3");
	ani->Add("AttackSitdownRight3");
	resourceManagement->Getanimations->Add(902, ani);

	//attack Sitdown right
	ani = new Animation(100);
	ani->Add("AttackSitdownLeft1");
	ani->Add("AttackSitdownLeft2");
	ani->Add("AttackSitdownLeft3");
	ani->Add("AttackSitdownLeft3");
	resourceManagement->Getanimations->Add(903, ani);

	AddAnimation(400);		// idle right
	AddAnimation(401);		// idle left
	AddAnimation(500);		// walk right
	AddAnimation(501);		// walk left

	AddAnimation(600);		//jump right
	AddAnimation(601);		//jump left

	AddAnimation(700);		//sitdown right
	AddAnimation(701);		//sitdown left

	//AddAnimation(800);		//facing backward

	AddAnimation(900);		//attack standing right
	AddAnimation(901);		//attack standing left
	AddAnimation(902);		//attack sitdown left
	AddAnimation(903);		//attack sitdown left


	SetPosition(0.0f, GROUND_POSITION);
}

void Simon::SetState(int state)
{
	this->state = state;
}

void Simon::OnKeyStateChange(BYTE * states)
{
	DirectInput* directInput = DirectInput::getInstance();

	switch (state)
	{
	case SIMON_STATE_IDLE:
		if (directInput->IsKeyDown(DIK_K))
		{
			SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else if (directInput->IsKeyDown(DIK_H))
		{
			SetState(SIMON_STATE_WALKING_LEFT);
		}
		else if (directInput->IsKeyDown(DIK_J))
		{
			SetState(SIMON_STATE_SITDOWN);
		}
		break;
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (directInput->IsKeyDown(DIK_J))
		{
			SetState(SIMON_STATE_SITDOWN);
		}
		break;
	}
}

void Simon::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (state)
	{
	case SIMON_STATE_IDLE:
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (KeyCode == DIK_X)
			SetState(SIMON_STATE_JUMPING);
		else if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_STAND);
		}
		break;
	case SIMON_STATE_JUMPING:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_JUMP);
		}
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_SITDOWN);
		}
	}
	
}

void Simon::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		if (KeyCode == DIK_K)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (KeyCode == DIK_H)
			SetState(SIMON_STATE_IDLE);
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_J)
			SetState(SIMON_STATE_IDLE);
		break;
	}
}

void Simon::Render()
{
	switch (state)
	{
	case SIMON_STATE_IDLE:
		if (nx == 1)
		{
			ani = SIMON_ANI_IDLE_RIGHT;
		}
		else
		{
			ani = SIMON_ANI_IDLE_LEFT;
		}
		break;
	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALKING_RIGHT;
		break;
	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALKING_LEFT;
		break;
	case SIMON_STATE_SITDOWN:
		if (nx == 1)
		{
			ani = SIMON_ANI_SITDOWN_RIGHT;
		}
		else
		{
			ani = SIMON_ANI_SITDOWN_LEFT;
		}
		break;
	}

	if (vy < 0)
	{
		if (nx == 1)
		{
			ani = SIMON_ANI_JUMPING_RIGHT;
		}
		else
		{
			ani = SIMON_ANI_JUMPING_LEFT;
		}
	}
	if (attacking)
	{
		if (nx == 1)
		{
			ani = SIMON_ANI_ATTACK_STANDING_RIGHT;
		}
		else
		{
			ani = SIMON_ANI_ATTACK_STANDING_LEFT;
		}
		attacking = false;
	}
	if (jumped || attacked)
	{
		SetState(SIMON_STATE_IDLE);
		jumped = false;
		attacked = false;
	}

	GameObject::animations[ani]->Render(x, y);
}

bool Simon::isOnGround()
{
	if (y == GROUND_POSITION)
		return true;
	return false;
}

void Simon::handleState()
{
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
	case SIMON_STATE_JUMPING:
		if (isOnGround())
		{
			vy = -SIMON_JUMP_SPEED_Y;
			jumped = true;
		}
		break;

	case SIMON_STATE_ATTACK_STAND:
		vx = 0;
		attacking = true;
		attacked = true;
		break;
	case SIMON_STATE_SITDOWN:
	case SIMON_STATE_ATTACK_SITDOWN:
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	}
}

Simon::~Simon()
{
	DirectInput* directInput = DirectInput::getInstance();

	__unhook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__unhook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__unhook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);
}
