#pragma once
#include "../GameObjects/Simon.h"
#include "../Screens/ScreenBase.h"
#include "../GameObjects/GameObject.h"
#include "../Input/DirectInput.h"
#include "../Viewport.h"
#include "../Game.h"


class GameplayScreen: public ScreenBase
{
private:

	vector<GameObject*> objects;
	Simon* simon;
	DirectInput* directInput;
	TileMap * tile_map;
	Sprite * Map;
	ResourceManagement* resourceManagement;
	RECT rect;
	Viewport* viewport;


public:

	void init() override;
	void update(float dt) override;
	void renderObject() override;
	void loadResources() override;
	
	GameplayScreen();
	~GameplayScreen();
};

