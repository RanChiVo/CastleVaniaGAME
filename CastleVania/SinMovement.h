#pragma once
#include "SpriteManagements/Sprite.h"
#include <d3dx9.h>

class SinMovement
{
private: 
	D3DXVECTOR2 amplitude;//Bien do A
	D3DXVECTOR2 linearVeloc;//Van toc tuyen tinh
	float radian;//φ
	float radianVeloc; // toc do goc ω

	LPSPRITE sprite;

public:
	SinMovement(D3DXVECTOR2 amplitude, float frequent);
	void setAmplitude(D3DXVECTOR2 amplitude);
	void Update(float dt);
	

	~SinMovement();
};

