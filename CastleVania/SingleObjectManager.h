#pragma once
#include "ResourceManagement.h"
#include "Animations/Animations.h"

class SingleObjectManager
{
protected: 
	ResourceManagement * resourceManagement;
	Animations* animations;

public:

	SingleObjectManager();
	~SingleObjectManager();
};

