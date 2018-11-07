#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <string>
#include "Animation.h"

class Animations
{
	static Animations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static Animations * GetInstance();
};