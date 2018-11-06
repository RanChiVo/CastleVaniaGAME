#include "Sprite.h"
#include "../CastleVania.h"

Sprite::Sprite(std::string id, RECT r, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->rect = r;
	this->texture = tex;
}

void Sprite::SetRECT(std::string id, RECT r)
{
	this->rect = r;
}

void Sprite::Draw(D3DXVECTOR2 postition)
{
	D3DXVECTOR3 p(postition.x, postition.y, 0);
	Direct3DManager* direct3D = Direct3DManager::getInstance();

	direct3D->GetSpriteHandler()->Draw(texture, &rect, nullptr, &p, D3DCOLOR_XRGB(255, 255, 255));;
}