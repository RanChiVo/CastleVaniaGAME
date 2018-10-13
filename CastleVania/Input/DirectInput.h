#pragma once
#include <dinput.h>
#include "../Game.h"
#include "../Debug/DebugOut.h"

class DirectInput
{
protected:

	static DirectInput* __instance;
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];
	LPKEYEVENTHANDLER keyEventHandler;
	DIDEVICEOBJECTDATA keyEvents[keyboard_buffer_size];
	DirectInput();

public:
	
	static DirectInput* getInstance();
	void initKeyboard(LPKEYEVENTHANDLER keyEventHandler, HWND hWnd);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	
	~DirectInput();
};

