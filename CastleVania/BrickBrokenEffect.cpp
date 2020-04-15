#include "BrickBrokenEffect.h"


BrickBrokenEffect::BrickBrokenEffect(D3DXVECTOR2 position)
{
	totalEffect = 4;

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
	speech_X[3] = -0.01f;

	speech_Y[0] = -0.07f;
	speech_Y[1] = -0.1f;
	speech_Y[2] = -0.05f;
	speech_Y[3] = -0.02f;

	//AddAnimation(ANI_EFFECT_BRICK);	
	currentAnimation = ANI_EFFECT_BRICK;
}

BrickBrokenEffect::~BrickBrokenEffect()
{
}
