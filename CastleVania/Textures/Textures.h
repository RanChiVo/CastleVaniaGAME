#pragma once
#include <unordered_map>
#include "../Direct3DManager.h"
using namespace std;

class Textures
{
	static Textures * __instance ;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
	unordered_map<int, std::pair<int, int>> sizeObject;

public:
	
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	std::pair<int, int> GetSizeObject(int id);
	void setSizeObject(int id, int widthObject, int heightObject);
	unordered_map<int, LPDIRECT3DTEXTURE9> GetTextures();
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	void Clear();
	static Textures * GetInstance();
};