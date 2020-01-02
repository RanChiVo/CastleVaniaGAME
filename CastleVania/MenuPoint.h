#pragma once
#include "d3dx9.h"
#include <string>
#include <vector>
#include "GameObjects/Simon.h"
#include "../CastleVania/ResourceManagement.h"
#include "SpriteManagements/Sprite.h"
#include <vector>

class MenuPoint
{
private:
	ID3DXFont *font;
	RECT rect;
	string content;
	std::vector<LPGAMEOBJECT> Simon_Item;
	int start_time;
	int gameTime;
	int Score = 0;
	int healthSimon = 0;
	int healthDarkBat = 0;

	std::string score;
	std::string timeString;
	Sprite* HP;
	Sprite* enemy_HP1;
	Sprite* place_item1;
	Sprite* lost_HP;
	Sprite* menu;
	Sprite* subWeapon;
	DWORD startTime;
	ResourceManagement* resourceManagement;
	LPD3DXSPRITE spriteHandler;
	RECT R;
	Sprite* heart;
public:
	MenuPoint();
	void loadResource();
	void update();
	void Draw(	);
	~MenuPoint();
};

