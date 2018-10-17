#pragma once
#include "Game.h"
#include "Textures/Textures.h"
#include "GameObjects/Simon.h"
#include "SpriteManagements/Sprites.h"
#include "Animations/Animations.h"
#include "WindowUtil.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"

class CastleVania : public Game
{
private:

	static CastleVania * __instance;
	HINSTANCE hInstance;
	int nCmdShow;
	ScreenManager* screenmanager;
	CastleVania();

public:

	void Init(HINSTANCE hInstance, int nCmdShow);
	void renderObjects();
	void loadResource();
	void handleInput();
	void update(float dt);
	void run();

	static CastleVania * GetInstance();

	~CastleVania();
};
