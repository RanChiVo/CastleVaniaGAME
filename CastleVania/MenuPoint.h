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
	int scoreFinal = 0;
	int heartScore = 0;
	int healthSimon = 0;
	int healthDarkBat = 0;

	std::string heartScoreString;
	std::string heartScoreTempString;
	std::string scoreStringTemp;
	std::string scoreString;
	std::string timeStringTemp;
	std::string timeString;
	std::string stageString;
	std::string livesString;
	Sprite* HP;
	Sprite* enemy_HP1;
	Sprite* menu;
	Sprite* subWeapon;
	EntityID idSubWeapon;
	int stage;
	Sprite* subItem;
	EntityID idSubItem;
	unordered_map<EntityID, Sprite*> itemList;
	DWORD startTime;
	LPD3DXSPRITE spriteHandler;
	RECT R;
public:
	MenuPoint();
	void loadResource();
	void update(DWORD dt);
	void Draw(ID3DXFont* font);
	~MenuPoint();
};

