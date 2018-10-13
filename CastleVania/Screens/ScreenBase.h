#pragma once
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "../Input/DirectInput.h"


class ScreenBase
{
protected:
	DirectInput* directInput;

public:
	ScreenBase();

	bool virtual init() = 0;
	void virtual update(float deltatime) = 0;
	void virtual handleInput() = 0;
	void virtual loadResources() = 0;
	void virtual render() = 0;

	virtual~ScreenBase();
};

