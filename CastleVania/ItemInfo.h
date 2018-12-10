#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "EntityID.h"

class ItemInfo
{
	int id;
	std::string name;
	int height;
	int width;
	D3DXVECTOR2 position;
	EntityID idHiddenItem;
public:

	ItemInfo();
	ItemInfo(int id, std::string name, int height, int width, D3DXVECTOR2 position, EntityID idHiddenItem);
	int get_id();
	std::string get_name();
	int get_height();
	int get_width();
	D3DXVECTOR2 get_postition();
	EntityID get_idHiddenItem();

	~ItemInfo();
};

