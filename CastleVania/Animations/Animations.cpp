#include "Animations.h"

CAnimations * CAnimations::__instance = NULL;


void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}

void CAnimations::loadResource()
{
	LPANIMATION ani;

	ani = new Animation(100);
	ani->Add(10001);
	Add(400, ani);

	ani = new Animation(100);
	ani->Add(10011);
	Add(401, ani);


	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	Add(500, ani);

	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	Add(501, ani);

}

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}
