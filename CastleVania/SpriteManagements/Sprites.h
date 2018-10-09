#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprite.h"

using namespace std;

class Sprites
{
	static Sprites * __instance;

	unordered_map<int, LPSPRITE> spritesList;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static Sprites * GetInstance();
};