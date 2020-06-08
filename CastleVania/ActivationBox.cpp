#include "ActivationBox.h"
#include "VampireBat.h"
#include "Crown.h"
#include "GameObjects/Simon.h"
#include "Ghost.h"
#include "Fleamen.h"
#include "Skeleton.h"
#include "Raven.h"
#include "DarkBat.h"
#include "SpearKnight.h"

ActivationBox::ActivationBox(D3DXVECTOR2 pos, EntityID activatedObjecId, int height, int width)
{
	id = ID_ENTITY_ACTIVATEBOX;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->activatedObjecId = activatedObjecId;
	isActivate = false;
}

void ActivationBox::ActionObject(vector<LPGAMEOBJECT> *coObjects)
{
	switch (activatedObjecId)
	{
	case ID_ENTITY_CROWN:

		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_ENTITY_CROWN:
			{
				Crown *crown = dynamic_cast<Crown *>(coObjects->at(i));
				crown->startAction();
			}
			break;
			}
		}
		break;
	case ID_ENTITY_FLEAMEN:
		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_ENTITY_FLEAMEN:
			{
				Fleamen *fleamen = dynamic_cast<Fleamen *>(coObjects->at(i));
				if (fleamen->getName().compare(name) == 0)
				{
					fleamen->StartActivate();
				}
			}
			break;
			}
		}
		break;
	case ID_ENTITY_DARK_BAT:
		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_ENTITY_DARK_BAT:
			{
				DarkBat *darkBat = dynamic_cast<DarkBat *>(coObjects->at(i));
				darkBat->ActivateState();
			}
			break;
			}
		}
		break;
	case ID_ENTITY_GHOST:
		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
			case ID_ENTITY_GHOST:
			{
				Ghost *ghost = dynamic_cast<Ghost *>(coObjects->at(i));
				ghost->SetState(STATE_SHOW);
			}
			break;
			}
		}
		break;
	case ID_ENTITY_WHITE_SKELETON:
		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
				case ID_ENTITY_WHITE_SKELETON:
				{
					Skeleton*skeleton = dynamic_cast<Skeleton *>(coObjects->at(i));
					if (skeleton->getName().compare(name) == 0)
					{
						if (!isActivate && !skeleton->IsActive())
						{
							skeleton->SetActivate(true);
							skeleton->SetDistanceGoOutActivateArea(x + width);
						}
					}
				}
				break;
			}
		}
		break;
	case ID_ENTITY_VAMPIRE_BAT:
		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
				case ID_ENTITY_VAMPIRE_BAT:
				{
					VampireBat *vampireBat = dynamic_cast<VampireBat *>(coObjects->at(i));
					if (vampireBat->getName().compare(name) == 0)
					{
						if (!isActivate)
						{
							isActivate = true;
							vampireBat->SetState(VampireBat::VAMPIRE_STATE_ATTACK);
							vampireBat->SetIsActive(true);
						}
					}
				}
				break;
			}
		}
		break;
	case ID_ENTITY_RAVEN:
		for (int i = 0; i < (int)coObjects->size(); i++)
		{
			switch (coObjects->at(i)->getID())
			{
				case ID_ENTITY_RAVEN:
				{
					Raven *raven = dynamic_cast<Raven *>(coObjects->at(i));
					if (raven->getName().compare(name) == 0)
					{
						if (!isActivate)
						{
							isActivate = true;
							raven->Activate();
						}
					}
				}
				break;
			}
		}
		break;
	}
}

void ActivationBox::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void ActivationBox::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void ActivationBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
}

ActivationBox::~ActivationBox()
{
}
