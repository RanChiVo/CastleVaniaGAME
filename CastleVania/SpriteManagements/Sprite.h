#pragma once
#include "../Direct3DManager.h"
#include "../Flip.h"

class Sprite
{
private:
	std::string id;
	RECT rect;
	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite();

	Sprite(std::string id, RECT r, LPDIRECT3DTEXTURE9 tex);
	
	void SetRECT( RECT r);

	RECT getRect();
	
	std::string getID();

	LPDIRECT3DTEXTURE9 getText();

	void Draw(D3DXVECTOR2 position, int alpha);

	//void Draw(D3DXVECTOR2 position, int alpha);

	void Draw(D3DXVECTOR2 position, Flip flip, int alpha );
};

typedef Sprite * LPSPRITE;
