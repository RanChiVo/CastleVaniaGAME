#pragma once

#include <vector>
#include "Screens/ScreenBase.h"
#include "Debug/DebugOut.h"


class ScreenManager
{
private:

	std::vector<ScreenBase*> screens;

public:
	ScreenManager();

	bool init();
	void handleInput();
	void loadResources();
	void update(float dt);
	void renderObject();

	void addScreen(ScreenBase* scene);
	void removeScreen();
	void changeScreen(ScreenBase* scene);
	void clearScreen();

	ScreenBase* getScene();

	~ScreenManager();
};

