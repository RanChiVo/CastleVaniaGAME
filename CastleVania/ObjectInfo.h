#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "EntityID.h"

class ObjectInfo
{
private:
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
	float endViewport;
	std::string cellId;
	int nx;
	int ny;
public:
	ObjectInfo() {
		id = 0;
		name = "";
		height = 0;
		width = 0;
		position = D3DXVECTOR2{0, 0};
		idHiddenItem = "";
		objectId = "";
		ObjectType = "";
		enemyName = "";
		stairHeight = 0;
		startViewport = 0;
		endViewport = 0;
		cellId = "";
		nx = 0;
		ny = 0;
	}

	int get_id() { return id; }
	std::string get_name() { return name; }
	int get_height() { return height; }
	int get_width() { return width; }
	D3DXVECTOR2 get_postition() { return position; }
	std::string get_idHiddenItem() { return idHiddenItem; }
	std::string get_ObjectType() { return ObjectType; }
	std::string get_ObjectId() { return objectId; }
	std::string get_enemyName() { return enemyName; }
	int get_stairHeight() { return stairHeight; }
	float get_StartViewPort() { return startViewport; }
	float get_EndViewPort() { return endViewport; }
	std::string getCellId() { return cellId; }
	int get_nx() { return nx; }
	int get_ny() { return ny; }

	void set_id(int value) { id = value; };
	void set_name(std::string value) { name = value; };
	void set_height(int value) { height = value;};
	void set_width(int value) { width = value;};
	void set_position(D3DXVECTOR2 value) { position = value;};
	void set_idHiddenItem(std::string value) { idHiddenItem = value;};
	void set_ObjectId(std::string value) { objectId = value;};
	void set_ObjectType(std::string value) { ObjectType = value;};
	void set_enemyName(std::string value) { enemyName = value;};
	void set_stairHeight(int value) { stairHeight = value;};
	void set_cellId(std::string value) { cellId = value;};
	void set_nx(int value) { nx = value;};
	void set_ny(int value) { ny = value;};
	void set_startViewPort(float value) { startViewport = value;};
	void set_endViewPort(float value) { endViewport = value;};
};
