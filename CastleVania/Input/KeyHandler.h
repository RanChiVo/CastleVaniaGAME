#pragma once
#include "KeyEventHandler.h"

class KeyHandler :
	public KeyEventHandler
{
public:
	KeyHandler();
	~KeyHandler();

protected:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

