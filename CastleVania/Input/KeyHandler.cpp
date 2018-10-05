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
	CastleVania* game = CastleVania::GetInstance();
	if (game->IsKeyDown(DIK_RIGHT))		
		game->simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		game->simon->SetState(SIMON_STATE_WALKING_LEFT);
	else game->simon->SetState(SIMON_STATE_IDLE);
}

void KeyHandler::OnKeyDown(int KeyCode)
{
	CastleVania* game = CastleVania::GetInstance();
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		game->simon->SetState(SIMON_STATE_JUMP);
		break;
	}
}

void KeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
