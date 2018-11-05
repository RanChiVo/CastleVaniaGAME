#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../DebugOut/DebugOut.h"
#include <string.h>
#include "../Direct3DManager.h"
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
	D3DXVECTOR2 Position;
	
public:
	//Init sprite
	Sprite(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	
	void SetRECT(std::string id, int left, int top, int right, int bottom)
	{
		this->id = id;
		this->left = left;
		this->right = right;
		this->bottom = bottom;
	}

	void SetPosition(D3DXVECTOR2 position) { this->Position = position; }

	void Draw();
};

typedef Sprite * LPSPRITE;
