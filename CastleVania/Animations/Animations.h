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
	void Delete(int id);
	LPANIMATION Get(int id);
	void Clear();
	static Animations * GetInstance();
};

typedef vector<LPANIMATION> AnimationSet;

typedef AnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class AnimationSets
{
	static AnimationSets * __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	AnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);


	static AnimationSets * GetInstance();
};