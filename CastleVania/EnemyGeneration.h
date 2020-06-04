#pragma once
#include <vector>
#include "GameObjects/GameObject.h"

class EnemyGeneration
{
	DWORD startGenerateZombie = 0;
	int numberPosGenerateZombie = 0;
	int numberZombie = 0;
	static EnemyGeneration* _instance;
public:
	EnemyGeneration();
	static EnemyGeneration* getInstance();
	void GenerateEnemy(vector<LPGAMEOBJECT> *objects, DWORD dt);
	~EnemyGeneration();
};

