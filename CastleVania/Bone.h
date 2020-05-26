#pragma once
#include "GameObjects/GameObject.h"

class Bone: public GameObject
{
	DWORD startThrowNext = 0;
	DWORD startAttack = 0;
	bool isStart = false;
	bool isFinishNext = false;
public:
	Bone();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartThrow();
	void StartAttack();
	DWORD GetStartAttack();
	bool IsFinishNext() { return isFinishNext; }
	bool IsStart() { return isStart; }
	void SetIsStart(bool isStart) { this->isStart = isStart; }
	void SetIsFinishNext(bool isFinish) { this->isFinishNext = isFinish; }
	~Bone();
};

