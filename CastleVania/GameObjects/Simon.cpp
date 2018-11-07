#include "Simon.h"
constexpr auto GROUND_POSITION = 300;

Simon::Simon()
{
	DirectInput* directInput = DirectInput::getInstance();

	__hook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__hook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__hook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);

	SetState(SIMON_STATE_IDLE);
	currentAnimation = SIMON_ANI_IDLE_RIGHT;
	
	whip = new Whip(D3DXVECTOR2(x,y));
	whip->SetStateWhip(WHIP_HIT_STAND);
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
}

void Simon::loadResource()
{
	ResourceManagement*resourceManagement = ResourceManagement::GetInstance();

	LPANIMATION ani;
	
	//idle right
	ani = new Animation(100);
	ani->Add("WalkingRight4");
	resourceManagement->Getanimations->Add(SIMON_ANI_IDLE_RIGHT, ani);

	//idle left
	ani = new Animation(100);
	ani->Add("WalkingLeft4");
	resourceManagement->Getanimations->Add(SIMON_ANI_IDLE_LEFT, ani);

	// walk right
	ani = new Animation(100);
	ani->Add("WalkingRight1");
	ani->Add("WalkingRight2");
	ani->Add("WalkingRight3");
	ani->Add("WalkingRight4");
	resourceManagement->Getanimations->Add(SIMON_ANI_WALKING_RIGHT, ani);

	// walk left
	ani = new Animation(100);

	ani->Add("WalkingLeft1");
	ani->Add("WalkingLeft2");
	ani->Add("WalkingLeft3");
	ani->Add("WalkingLeft4");
	resourceManagement->Getanimations->Add(SIMON_ANI_WALKING_LEFT, ani);

	//jump right
	ani = new Animation(100);
	ani->Add("JumpRight");
	resourceManagement->Getanimations->Add(SIMON_ANI_JUMPING_RIGHT, ani);

	//jump left
	ani = new Animation(100);
	ani->Add("JumpLeft");
	resourceManagement->Getanimations->Add(SIMON_ANI_JUMPING_LEFT, ani);

	//sit down right
	ani = new Animation(100);
	ani->Add("SitdownRight");
	resourceManagement->Getanimations->Add(SIMON_ANI_SITDOWN_RIGHT, ani);

	//sit down left
	ani = new Animation(100);
	ani->Add("SitdownLeft");
	resourceManagement->Getanimations->Add(SIMON_ANI_SITDOWN_LEFT, ani);

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
	resourceManagement->Getanimations->Add(SIMON_ANI_ATTACK_STANDING_RIGHT, ani);

	//attack standing left
	ani = new Animation(100);
	ani->Add("AttackStandLeft1");
	ani->Add("AttackStandLeft2");
	ani->Add("AttackStandLeft3");
	resourceManagement->Getanimations->Add(SIMON_ANI_ATTACK_STANDING_LEFT, ani);

	//attack Sitdown right
	ani = new Animation(100);
	ani->Add("AttackSitdownRight1");
	ani->Add("AttackSitdownRight2");
	ani->Add("AttackSitdownRight3");
	resourceManagement->Getanimations->Add(SIMON_ANI_ATTACK_SITDOWN_RIGHT, ani);

	//attack Sitdown right
	ani = new Animation(100);
	ani->Add("AttackSitdownLeft1");
	ani->Add("AttackSitdownLeft2");
	ani->Add("AttackSitdownLeft3");
	resourceManagement->Getanimations->Add(SIMON_ANI_ATTACK_SITDOWN_LEFT, ani);

	AddAnimation(SIMON_ANI_IDLE_LEFT);		// idle right
	AddAnimation(SIMON_ANI_IDLE_RIGHT);		// idle left
	AddAnimation(SIMON_ANI_WALKING_LEFT);		// walk right
	AddAnimation(SIMON_ANI_WALKING_RIGHT);		// walk left

	AddAnimation(SIMON_ANI_JUMPING_RIGHT);		//jump right
	AddAnimation(SIMON_ANI_JUMPING_LEFT);		//jump left

	AddAnimation(SIMON_ANI_SITDOWN_RIGHT);		//sitdown right
	AddAnimation(SIMON_ANI_SITDOWN_LEFT);		//sitdown left

	//AddAnimation(800);		//facing backward

	AddAnimation(SIMON_ANI_ATTACK_STANDING_RIGHT);		//attack standing right
	AddAnimation(SIMON_ANI_ATTACK_STANDING_LEFT);		//attack standing left
	AddAnimation(SIMON_ANI_ATTACK_SITDOWN_RIGHT);		//attack sitdown left
	AddAnimation(SIMON_ANI_ATTACK_SITDOWN_LEFT);		//attack sitdown right

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
		else if (directInput->IsKeyDown(DIK_J)  && isOnGround())
		{
			SetState(SIMON_STATE_SITDOWN);
		}
		break;
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_WALKING_LEFT:
		if (directInput->IsKeyDown(DIK_J) && isOnGround())
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
			whip->SetStateWhip(WHIP_HIT_STAND);
		}
		break;
	case SIMON_STATE_JUMPING:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_JUMP);
			whip->SetStateWhip(WHIT_HIT_JUMP);
		}
		if (KeyCode == DIK_J)
		{
			SetState(SIMON_STATE_IDLE);
		}
		break;
	case SIMON_STATE_SITDOWN:
		if (KeyCode == DIK_Z)
		{
			SetState(SIMON_STATE_ATTACK_SITDOWN);
			whip->SetStateWhip(WHIT_HIT_SITDOWN);
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
	if (animations.find(currentAnimation)->second != nullptr)
	{
		animations.find(currentAnimation)->second->Render(x, y);
		
		whip->draw(state, nx);
	}
	else return;
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
		checkRewind = true;
		currentAnimation = SIMON_ANI_WALKING_RIGHT;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_MOVE_SPEED;
		nx = -1;
		checkRewind = true;
		currentAnimation = SIMON_ANI_WALKING_LEFT;
		break;

	case SIMON_STATE_JUMPING:
		if (!jumped)
		{
			jumped = true;
			vy = -SIMON_JUMP_SPEED_Y;
			break;
		}
		
		if (vy < 0)
		{
			if (nx == 1) currentAnimation = SIMON_ANI_JUMPING_RIGHT;
			else currentAnimation = SIMON_ANI_JUMPING_LEFT;
		}
		else
		{
			if (nx == 1) currentAnimation = SIMON_ANI_IDLE_RIGHT;
			else currentAnimation = SIMON_ANI_IDLE_LEFT;
		}

		if (isOnGround() && jumped)
		{
			SetState(SIMON_STATE_IDLE);
			jumped = false;
		}
		checkRewind = false;
		break;

	case SIMON_STATE_ATTACK_STAND:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_ATTACK_STANDING_RIGHT;
		else currentAnimation = SIMON_ANI_ATTACK_STANDING_LEFT;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_SITDOWN:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_SITDOWN_RIGHT;
		else currentAnimation = SIMON_ANI_SITDOWN_LEFT;
		break;

	case SIMON_STATE_ATTACK_SITDOWN:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_ATTACK_SITDOWN_RIGHT;
		else currentAnimation = SIMON_ANI_ATTACK_SITDOWN_LEFT;
		Reset(currentAnimation);
		break;

	case SIMON_STATE_IDLE:
		vx = 0;
		checkRewind = false;
		if (nx == 1) currentAnimation = SIMON_ANI_IDLE_RIGHT;
		else currentAnimation = SIMON_ANI_IDLE_LEFT;
		break;
	}

	animations.find(currentAnimation)->second->SetLoop(checkRewind);
}

void Simon::Reset(int currentAnimation)
{
	if (animations.find(currentAnimation)->second->IsFinished())
	{
		SetState(SIMON_STATE_IDLE);
		animations.find(currentAnimation)->second->SetFinish(false);
	}
}

Simon::~Simon()
{
	DirectInput* directInput = DirectInput::getInstance();

	__unhook(&DirectInput::KeyState, directInput, &Simon::OnKeyStateChange);
	__unhook(&DirectInput::OnKeyDown, directInput, &Simon::OnKeyDown);
	__unhook(&DirectInput::OnKeyUp, directInput, &Simon::OnKeyUp);
}
