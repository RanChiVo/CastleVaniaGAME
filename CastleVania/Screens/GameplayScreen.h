#pragma once
#include "../GameObjects/Simon.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Input/DirectInput.h"

class GameplayScreen: public ScreenBase
{
private:

	vector<GameObject*> objects;
	Simon* simon;
	DirectInput* directInput;

public:

	void init() override;
	void update(float dt) override;
	void renderObject() override;
	void loadResources() override;
	
	GameplayScreen();
	~GameplayScreen();
};

