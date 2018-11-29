#include "Animations.h"
#include "../SpriteManagements/Sprites.h"

Animations * Animations::__instance = nullptr;

void Animations::Add(int id, LPANIMATION ani)
{
	animations.emplace(id, ani);
}

LPANIMATION Animations::Get(int id)
{
	return animations.find(id)->second;
}

Animations * Animations::GetInstance()
{
	if (__instance == nullptr) __instance = new Animations();
	return __instance;
}
