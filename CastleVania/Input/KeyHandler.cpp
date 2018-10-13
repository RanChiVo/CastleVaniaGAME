#include "KeyHandler.h"
#include "../Debug/DebugOut.h"
#include <dinput.h>
#include "../GameObjects/Simon.h"
#include "../CastleVania.h"

KeyHandler::KeyHandler()
{
} 

KeyHandler::~KeyHandler()
{
}

void KeyHandler::KeyState(BYTE * states)
{
	DirectInput* directInput = DirectInput::getInstance();
	CastleVania* game = CastleVania::GetInstance();

	if (directInput->IsKeyDown(DIK_K))
	{
		game->simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (directInput->IsKeyDown(DIK_H))
	{
		game->simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (directInput->IsKeyDown(DIK_J))
	{
		if (game->simon->GetDierection() > 0)
		{
			game->simon->SetState(SIMON_STATE_SITDOWN_RIGHT);
		}
		else
		{
			game->simon->SetState(SIMON_STATE_SITDOWN_LEFT);
		}
	}
	else game->simon->SetState(SIMON_STATE_IDLE);
}

void KeyHandler::OnKeyDown(int KeyCode)
{
	CastleVania* game = CastleVania::GetInstance();
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	
	if (KeyCode == DIK_X)
	{
		if (game->simon->GetDierection() > 0)
		{
			game->simon->SetState(SIMON_STATE_JUMPING_RIGHT);
		}
		else
		{
			game->simon->SetState(SIMON_STATE_JUMPING_LEFT);
		}
	}
}

void KeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
