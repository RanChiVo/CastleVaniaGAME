#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprite.h"

#define ID_TEX_SIMON 0
using namespace std;

class Sprites
{
	static Sprites * __instance;

	unordered_map<int, LPSPRITE> spritesList;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void loadResource();


	static Sprites * GetInstance();
};