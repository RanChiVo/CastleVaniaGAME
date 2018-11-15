#include "Sprite.h"
#include "../CastleVania.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string id, RECT r, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->rect = r;
	this->texture = tex;
}

void Sprite::SetRECT( RECT r)
{
	this->rect = r;
}

RECT Sprite::getRect()
{
	return rect;
}

void Sprite::Draw(D3DXVECTOR2 position)
{
	D3DXVECTOR3 p(position.x, position.y, 0);
	Direct3DManager* direct3D = Direct3DManager::getInstance();

	direct3D->GetSpriteHandler()->Draw(texture, &rect, nullptr, &p, D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::Draw(D3DXVECTOR2 position, int alpha)
{
	D3DXVECTOR3 p(position.x, position.y, 0);
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	direct3D->GetSpriteHandler()->Draw(texture, &rect, nullptr, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}
