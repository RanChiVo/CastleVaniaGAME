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
	std::vector<Sprite*> HPlist;
	std::vector<Sprite*> enemy_HPList;
	std::vector<LPGAMEOBJECT> Simon_Item;
	int start_time;
	

	int score;
	std::string timeString;
	int item;
	int blood_simon;
	int state;
	int weapon;
	Sprite* HP;
	DWORD startTime;

	ResourceManagement* resourceManagement;

public:
	MenuPoint();
	void update();
	void Draw(	);
	~MenuPoint();
};

