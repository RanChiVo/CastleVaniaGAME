#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../DebugOut/DebugOut.h"
#include <string.h>
using namespace std;

class Sprite
{
private:
	std::string id;
	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	//Init sprite
	Sprite(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	
	void Set(std::string id, int left, int top, int right, int bottom)
	{
		this->id = id;
		this->left = left;
		this->right = right;
		this->bottom = bottom;
	}

	void Draw(float x, float y);

};

typedef Sprite * LPSPRITE;
