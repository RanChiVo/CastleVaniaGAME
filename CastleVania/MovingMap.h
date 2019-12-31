#pragma once
#include "EntityID.h"
#include "StaticObject.h"

class MovingMap 
{
private:
	EntityID idMap;
	static MovingMap* _instance;
	MovingMap();
public:
	static MovingMap* getInstance();
	EntityID getIdMap() { return idMap; };
	void setIdMap(EntityID idMap) { this->idMap = idMap; }
	
	~MovingMap();
};

