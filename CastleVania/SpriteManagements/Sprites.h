#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Sprite.h"
#include <string>
using namespace std;

class Sprites
{
	static Sprites * __instance;

	unordered_map<std::string, LPSPRITE> spritesList;

public:
	void Add(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(std::string id);

	static Sprites * GetInstance();
};