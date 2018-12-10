#include "ItemInfo.h"



ItemInfo::ItemInfo()
{
}

ItemInfo::ItemInfo(int id, std::string name, int height, int width, D3DXVECTOR2 position, EntityID idHiddenItem)
{
	this->id = id;
	this->name = name;
	this->height = height;
	this->position = position;
	this->idHiddenItem = idHiddenItem;
}

int ItemInfo::get_id()
{
	return this->id;
}

std::string ItemInfo::get_name()
{
	return name;
}

int ItemInfo::get_height()
{
	return height;
}

int ItemInfo::get_width()
{
	return width;
}

D3DXVECTOR2 ItemInfo::get_postition()
{
	return D3DXVECTOR2();
}

EntityID ItemInfo::get_idHiddenItem()
{
	return EntityID();
}

ItemInfo::~ItemInfo()
{
}
