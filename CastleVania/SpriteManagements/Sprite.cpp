#include "Sprite.h"
#include "../CastleVania.h"

Sprite::Sprite(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void Sprite::Draw()
{
	D3DXVECTOR3 p(Position.x, Position.y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	Direct3DManager* direct3D = Direct3DManager::getInstance();
	direct3D->GetSpriteHandler()->Draw(texture, &r, nullptr, &p, D3DCOLOR_XRGB(255, 255, 255));;
}