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

	unordered_map<std::string, LPSPRITE> sprites;

public:

	void Add(std::string id, RECT r, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(std::string id);
	void Clear();
	static Sprites * GetInstance();
};