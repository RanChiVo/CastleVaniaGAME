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

std::string Sprite::getID()
{
	return id;
}

LPDIRECT3DTEXTURE9 Sprite::getText()
{
	return texture;
}

void Sprite::Draw(D3DXVECTOR2 position, int alpha)
{
	D3DXVECTOR3 p(floor(position.x), floor(position.y), 0);
	Direct3DManager* direct3D = Direct3DManager::getInstance();

	direct3D->GetSpriteHandler()->Draw(texture, &rect, nullptr, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

void Sprite::Draw(D3DXVECTOR2 position, Flip flip, int alpha)
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	D3DXVECTOR3 p2(position.x, position.y, 0);
	D3DXVECTOR2 scale = D3DXVECTOR2{ 1, 1 };
	D3DXMATRIX afterScale;

	D3DXVECTOR2 center;

	center.x = position.x + (rect.right - rect.left) / 2;
	center.y = position.y + (rect.bottom - rect.top) / 2;
	D3DXMATRIX beforeScale;
	direct3D->GetSpriteHandler()->GetTransform(&beforeScale);

	switch (flip)
	{
	case normal:
		break;
	case flip_horiz:
		scale.x = -1;
		scale.y = 1;
		break;
	case flip_vert:
		scale.x = 1;
		scale.y = -1;
		break;
	}

	D3DXMatrixScaling(&afterScale, scale.x, scale.y, .0f);

	D3DXMatrixTransformation2D(
		&afterScale,
		&center,   
		0.0f,      
		&scale,  
		&center,    
		0.0f,
		nullptr     
	);
	
	direct3D->GetSpriteHandler()->SetTransform(&afterScale);

	direct3D->GetSpriteHandler()->Draw(texture, &rect, nullptr, &p2, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	direct3D->GetSpriteHandler()->SetTransform(&beforeScale);
}
