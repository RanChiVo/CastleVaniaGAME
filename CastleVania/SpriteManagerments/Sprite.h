#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../Debug/DebugOut.h"

using namespace std;

class Sprite
{
private:

	int id;
	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	//Init sprite
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y);

};

typedef Sprite * LPSPRITE;
