#pragma once
#include "../DebugOut/DebugOut.h"
#include <stdio.h>  

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// evh_native.cpp  
constexpr int keyboard_buffer_size = 1024;

[event_source(native)]
class DirectInput
{
protected:

	static DirectInput* __instance;
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[keyboard_buffer_size];
	DirectInput();

public:
	
	__event void KeyState(BYTE *state);
	__event void OnKeyDown(int KeyCode);
	__event void OnKeyUp(int KeyCode);

	bool isPlayGame = false;

	void initKeyboard(HWND hWnd);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	LPDIRECTINPUTDEVICE8 getdidv() { return didv; }
	DIDEVICEOBJECTDATA getKeyEvents(int i) { return keyEvents[i]; }

	static DirectInput* getInstance();

	~DirectInput();
};

