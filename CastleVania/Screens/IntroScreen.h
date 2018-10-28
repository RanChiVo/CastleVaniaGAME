#pragma once
#include "ScreenBase.h"
#include "../ViewPort.h"

class IntroScreen : public ScreenBase
{
public:

	void init() override;
	void update(float dt) override;
	void renderObject() override;
	void loadResources() override;

	IntroScreen();
	~IntroScreen();
};

