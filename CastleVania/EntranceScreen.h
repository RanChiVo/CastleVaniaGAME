#pragma once
#include "Screens/ScreenBase.h"

class EntranceScreen : public ScreenBase
{
public:
	EntranceScreen();
	void virtual update(DWORD dt);
	void updateViewport(DWORD dt);
	void virtual loadResources();
	~EntranceScreen();
};

