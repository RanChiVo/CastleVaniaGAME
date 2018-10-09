#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800
constexpr int keyboard_buffer_size = 1024;

class  KeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	virtual ~KeyEventHandler() {};
};
typedef KeyEventHandler * LPKEYEVENTHANDLER;
