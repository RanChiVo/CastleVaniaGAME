#include "Animations.h"

Animations * Animations::__instance = nullptr;
AnimationSets * AnimationSets::__instance = nullptr;

Animations::Animations()
{
}

void Animations::Add(int id, LPANIMATION ani)
{
	animations.emplace(id, ani);
}

void Animations::Delete(int id)
{
	animations.erase(id);
}

LPANIMATION Animations::Get(int id)
{
	return animations.find(id)->second;
}

void Animations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}

Animations * Animations::GetInstance()
{
	if (__instance == nullptr) __instance = new Animations();
	return __instance;
}

AnimationSets::AnimationSets()
{
	
}

AnimationSets * AnimationSets::GetInstance()
{
	if (__instance == NULL) __instance = new AnimationSets();
	return __instance;
}

void AnimationSets::Add(int id, LPANIMATION_SET ani_set)
{
	animation_sets[id] = ani_set;
}

LPANIMATION_SET AnimationSets::Get(unsigned int id)
{
	LPANIMATION_SET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n", id);

	return ani_set;
}

