#include "EnemyGeneration.h"
#include "ActivationBox.h"
#include "Direct3DManager.h"
#include "GameObjects/Zombie.h"

constexpr DWORD TIME_GERATE_ZOMBIE = 5000;
EnemyGeneration* EnemyGeneration::_instance = nullptr;

EnemyGeneration::EnemyGeneration()
{
}

EnemyGeneration * EnemyGeneration::getInstance()
{
	if (_instance == nullptr)
		_instance = new EnemyGeneration();
	return _instance;
}

void EnemyGeneration::GenerateEnemy(vector<LPGAMEOBJECT> *objects, DWORD dt)
{
	if (startGenerateZombie > 0 && GetTickCount() - startGenerateZombie >= TIME_GERATE_ZOMBIE)
	{
		startGenerateZombie = 0;
	}

	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->getID() == ID_ENTITY_ACTIVATEBOX)
		{
			ActivationBox *ps = dynamic_cast<ActivationBox *>(objects->at(i));
			float portalLeft, portalTop, portalRight, portalBottom;
			ps->GetBoundingBox(portalLeft, portalTop, portalRight, portalBottom);
			float viewportRight = Direct3DManager::getInstance()->getViewport()->getX() 
				+ Direct3DManager::getInstance()->getViewport()->getWidth();
			float viewportLeft = Direct3DManager::getInstance()->getViewport()->getX();

			switch (ps->GetActivatedObjecId())
			{
			case ID_ENTITY_ZOMBIE:
				if (startGenerateZombie == 0)
				{
					numberPosGenerateZombie += 1;
					if (numberPosGenerateZombie == 1)
					{
						numberZombie = 1;
					}
					else numberZombie = 2;
					
					if (numberPosGenerateZombie >= 2)
					{
						startGenerateZombie = GetTickCount();
						numberPosGenerateZombie = 0;
					}

					if (viewportRight <= portalRight)
					{
						for (int i = 0; i < numberZombie; i++)
						{
							Zombie* zombie = new Zombie();
							zombie->set_nx(-1);
							zombie->SetPosition(D3DXVECTOR2(portalRight - 60 * i, portalBottom - zombie->getHeight()));
							zombie->SetState(ZOMBIE_STATE_WALKING);
							objects->push_back(zombie);
						}
					}
					else if (viewportLeft >= portalLeft)
					{
						for (int i = 0; i < numberZombie; i++)
						{
							Zombie* zombie = new Zombie();
							zombie->set_nx(1);
							zombie->SetPosition(D3DXVECTOR2(portalLeft + 60 * i, portalBottom - zombie->getHeight()));
							zombie->SetState(ZOMBIE_STATE_WALKING);
							objects->push_back(zombie);
						}
					}
				}
			break;
			}
		}
	}
}

EnemyGeneration::~EnemyGeneration()
{
}
