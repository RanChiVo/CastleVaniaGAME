#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "EntityID.h"

class ObjectInfo
{
public:
	class builder;
	ObjectInfo(int id, std::string name, int height,
		int width,
		D3DXVECTOR2 position,
		std::string idHiddenItem,
		std::string objectId,
		std::string ObjectType,
		std::string enemyName,
		int stairHeight, float startViewport, int nx, int ny) :id{ id }, name{ name }, height{ height }, width{ width }, position{ position },
		idHiddenItem{ idHiddenItem }, objectId{ objectId }, ObjectType{ ObjectType }, enemyName{ enemyName }, stairHeight{ stairHeight }, startViewport{ startViewport }, nx{ nx }, ny{ ny }
	{}

	int id;
	std::string name;
	int height;
	int width;
	D3DXVECTOR2 position;
	std::string idHiddenItem;
	std::string objectId;
	std::string ObjectType;
	std::string enemyName;
	int stairHeight;
	float startViewport;
	int nx;
	int ny;
};

class ObjectInfo::builder
{
public:
	builder& set_id(int value) { id = value; return *this; };
	builder& set_name(std::string value) { name = value; return *this; };
	builder& set_height(int value) { height = value; return *this; };
	builder& set_width(int value) { width = value; return *this; };
	builder& set_position(D3DXVECTOR2 value) { position = value; return *this; };
	builder& set_idHiddenItem(std::string value) { idHiddenItem = value; return *this; };
	builder& set_ObjectId(std::string value) { objectId = value; return *this; };
	builder& set_ObjectType(std::string value) { ObjectType = value; return *this; };
	builder& set_enemyName(std::string value) { enemyName = value; return *this; };
	builder& set_stairHeight(int value) { stairHeight = value; return *this; };
	builder& set_nx(int value) { nx = value; return *this; };
	builder& set_ny(int value) { ny = value; return *this; };
	builder& set_startViewPort(int value) { startViewport = value; return *this; };

	std::string get_name() { return name; }
	int get_height() { return height; }
	int get_width() { return width; }
	D3DXVECTOR2 get_postition() { return position; }
	std::string get_idHiddenItem() { return idHiddenItem; }
	std::string get_ObjectType() { return ObjectType; }
	std::string get_ObjectId() { return objectId; }
	std::string get_enemyName() { return enemyName; }
	int get_stairHeight() { return stairHeight; }
	int get_StartViewPort() { return startViewport; }
	int get_nx() { return nx; }
	int get_ny() { return ny; }

	ObjectInfo build() const
	{
		return ObjectInfo{ id, name, height, width, position, idHiddenItem, objectId , ObjectType, enemyName, stairHeight, startViewport, nx, ny };
	}

private:
	int id = 0;
	std::string name = "";
	int height = 0;
	int width = 0;
	D3DXVECTOR2 position;
	std::string idHiddenItem = "";
	std::string objectId = "";
	std::string ObjectType = "";
	std::string enemyName = "";
	int stairHeight = 0;
	float startViewport = 0;
	int nx = 0;
	int ny = 0;
};
