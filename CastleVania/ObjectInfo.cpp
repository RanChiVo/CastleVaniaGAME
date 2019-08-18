#include "ObjectInfo.h"


ObjectInfo::ObjectInfo()
{
}

ObjectInfo::ObjectInfo(int id, std::string name, int height, int width, D3DXVECTOR2 position, std::string idHiddenItem)
{
	this->id = id;
	this->name = name;
	this->height = height;
	this->width = width;
	this->position = position;
	this->idHiddenItem = idHiddenItem;
}

int ObjectInfo::get_id()
{
	return this->id;
}

std::string ObjectInfo::get_name()
{
	return this->name;
}

int ObjectInfo::get_height()
{
	return this->height;
}

int ObjectInfo::get_width()
{
	return this->width;
}

D3DXVECTOR2 ObjectInfo::get_postition()
{
	return this->position;
}

std::string ObjectInfo::get_idHiddenItem()
{
	return this->idHiddenItem;
}

ObjectInfo::~ObjectInfo()
{
}
