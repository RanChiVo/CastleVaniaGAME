#include "Item.h"

Item::Item(EntityID idItem, D3DXVECTOR2 position)
{
	SetPosition(position);
	switch (idItem)
	{
	case ID_ENTITY_HEART:
		break;
	case ID_ENTITY_SMALL_HEART:
		break;
	case ID_ENTITY_EFFECT:
		break;
	case ID_ENTITY_WEAPON_REWARD:
		break;
	case ID_ENTITY_DAGGER:
		break;
	case ID_ENTITY_FIRE_BOMB:
		break;
	case ID_ENTITY_MIRACULOUS_BAG:
		break;
	case ID_ENTITY_RED_100_MIRACULOUS_BAG:
		break;
	case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
		break;
	case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
		break;
	case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
		break;
	case ID_ENTITY_CROSS:
		break;
	case ID_ENTITY_STOP_WATCH:
		break;
	default:
		break;
	}
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void Item::Render(Viewport * viewport)
{
}


Item::~Item()
{
}
