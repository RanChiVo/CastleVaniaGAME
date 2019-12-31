#pragma once
#include <utility>      
#include <iostream>
#include <string>
#include <map>
#include <set> 
#include "GameObjects/GameObject.h"

constexpr int HIEGHT_GRID = 256;
constexpr int WIDTH_GRID = 256;

class Grid
{
	int row, col;
	set<LPGAMEOBJECT>** staticObjects;
	set<LPGAMEOBJECT> dynamicObjects;
public:
	Grid(int row, int col);
	void loadObjects(vector<LPGAMEOBJECT>* coObjects);
	void updateObjects(vector<LPGAMEOBJECT>* coObjects);
	void update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	~Grid();
};

