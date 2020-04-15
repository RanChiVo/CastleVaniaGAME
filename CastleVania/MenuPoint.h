#pragma once
#include <string>
#include <vector>
#include "GameObjects/Simon.h"
#include "SpriteManagements/Sprite.h"
#include "SpriteManagements/Sprites.h"
#include <vector>

class MenuPoint
{
private:
	ID3DXFont *font;
	RECT rect;
	std::string content;
	std::vector<LPGAMEOBJECT> Simon_Item;
	int start_time;
	int gameTime;
	int score = 0;
	int healthSimon = 0;
	int healthDarkBat = 0;

	std::string heartScore;
	std::string scoreStringTemp;
	std::string scoreString;
	std::string timeString;
	Sprite* HP;
	Sprite* enemy_HP1;
	Sprite* place_item1;
	Sprite* lost_HP;
	Sprite* menu;
	Sprite* subWeapon;
	EntityID idSubWeapon;
	unordered_map<EntityID, Sprite*> itemList;
	DWORD startTime;
//	ResourceManagement* resourceManagement;
	LPD3DXSPRITE spriteHandler;
	RECT R;
	Sprite* heart;
public:
	MenuPoint();
	void loadResource();
	void update();
	void Draw(ID3DXFont* font);
	~MenuPoint();
};

