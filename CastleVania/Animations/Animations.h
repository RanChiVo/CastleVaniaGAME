#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Animation.h"

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void loadResource();

	static CAnimations * GetInstance();
};