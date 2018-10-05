#pragma once
#include "Game.h"
#include "Textures/Textures.h"
#include "Input/KeyHandler.h"
#include "GameObjects/Simon.h"
#include "SpriteManagerments/Sprites.h"
#include "Animations/Animations.h"
#include "WindowUtil.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

class CastleVania: public Game
{
private:

	static CastleVania * __instance;
	CastleVania();

public:

	void init(HINSTANCE hInstance, int nCmdShow);
	void loadResource();
	void run();

	static CastleVania * GetInstance();

	~CastleVania();
};

