#include "MovingMap.h"
#include "GameObjects/Simon.h"

MovingMap* MovingMap::_instance = nullptr;

MovingMap::MovingMap()
{
	idMap = ID_ENTITY_MAP_PLAYGAME;
}

MovingMap * MovingMap::getInstance()
{
	if (_instance == nullptr)
		_instance = new MovingMap();
	return _instance;
}

MovingMap::~MovingMap()
{
}
