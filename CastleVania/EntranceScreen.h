#pragma once
#include "Screens/ScreenBase.h"

class EntranceScreen : public ScreenBase
{
public:
	EntranceScreen();
	void update(DWORD dt);
	void updateViewport(DWORD dt);
	~EntranceScreen();
};

