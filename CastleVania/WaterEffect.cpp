#include "WaterEffect.h"



WaterEffect::WaterEffect(D3DXVECTOR2 position)
{
	totalEffect = 3;

	position_X = new float[totalEffect];
	position_Y = new float[totalEffect];
	speech_X = new float[totalEffect];
	speech_Y = new float[totalEffect];

	for (int i = 0; i < totalEffect; i++)
	{
		position_X[i] = position.x;
		position_Y[i] = position.y;
	}

	speech_X[0] = 0.03f;
	speech_X[1] = 0.008f;
	speech_X[2] = -0.02f;

	speech_Y[0] = -0.07f;
	speech_Y[1] = -0.1f;
	speech_Y[2] = -0.05f;

	AddAnimation(ANI_EFFECT_WATER);
	currentAnimation = ANI_EFFECT_WATER;
}


WaterEffect::~WaterEffect()
{
}
