#pragma once
#include "Game.h"
#include "Textures/Textures.h"
#include "GameObjects/Simon.h"
#include "SpriteManagements/Sprites.h"
#include "Animations/Animations.h"
#include "WindowUtil.h"
#include "Screens/ScreenBase.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include "Screens/GameplayScreen.h"


class CastleVania : public Game
{
private:

	static CastleVania * __instance;

	HINSTANCE hInstance;
	int nCmdShow;

	ScreenManager* screenmanager;
	MenuScreen* menuscreen;
	GameplayScreen* gameplayscreen;

	CastleVania();

public:

	void Init(HINSTANCE hInstance, int nCmdShow);
	void renderObjects();
	void loadResource();
	void update(float dt);
	void run();

	void playGame(ScreenBase* screen);

	static CastleVania * GetInstance();

	~CastleVania();
};
