#include "SpawnEnemy.h"
#include "GameObjects/Simon.h"

SpawnEnemy::SpawnEnemy()
{
	id = ID_ENTITY_SPAWN_ENEMY;
}

void SpawnEnemy::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void SpawnEnemy::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void SpawnEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	float left1, top1, right1, bottom1;
	Simon::getInstance()->GetBoundingBox(left1, top1, right1, bottom1);
	RECT rect1 = RECT{ long(left1), long(top1), long(right1), long(bottom1) };

	float left2, top2, right2, bottom2;

	GetBoundingBox(left2, top2, right2, bottom2);

	RECT rect2 = RECT{ long(left2), long(top2), long(right2), long(bottom2) };

	bool result = this->checkCollision(rect1, rect2);

	if (result)
	{
		if (name.compare("Spawn Fish Man") == 0)
		{
			Simon::getInstance()->setIsInSpawn(true);
			Simon::getInstance()->setIdEnemySpawn(ID_ENTITY_FISH_MAN);
		}
		else if (name.compare("Spawn Bat") == 0)
		{
			Simon::getInstance()->setIsInSpawn(true);
			Simon::getInstance()->setIdEnemySpawn(ID_ENTITY_VAMPIRE_BAT);
		}
		else if (name.compare("Spawn Zombie") == 0)
		{
			Simon::getInstance()->setIsInSpawn(true);
			Simon::getInstance()->setIdEnemySpawn(ID_ENTITY_ZOMBIE);
		}
		else Simon::getInstance()->setIsInSpawn(false);
	}
}


SpawnEnemy::~SpawnEnemy()
{
}
