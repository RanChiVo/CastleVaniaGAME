#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "EntityID.h"


class ObjectInfo
{
	int id;
	std::string name;
	int height;
	int width;
	D3DXVECTOR2 position;
	std::string idHiddenItem;
	std::string objectId;
	std::string ObjectType;
public:

	ObjectInfo();
	ObjectInfo(int id, std::string name, int height, int width, D3DXVECTOR2 position, std::string idHiddenItem, std::string objectId);
	int get_id();
	std::string get_name();
	int get_height();
	int get_width();
	D3DXVECTOR2 get_postition();
	std::string get_idHiddenItem();
	std::string get_ObjectType();
	std::string get_ObjectId();
	~ObjectInfo();
};

