#include "ActivationBox.h"
#include "VampireBat.h"
#include "Crown.h"
#include "GameObjects/Simon.h"

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
					}
				}
				break;
			}
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
	if (isActivate)
	{
		setWidth(512);
		setHeight(512);
	}

	if (activatedObjecId == ID_ENTITY_VAMPIRE_BAT && isActivate)
	{
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		float sl, st, sr, sb;
		Simon::getInstance()->GetBoundingBox(sl, st, sr, sb);

		if (!(checkCollision(RECT{ long(sl), long(st), long(sr), long(sb) }, RECT{ long(l), long(t), long(r), long(b) })))
		{
			for (int i = 0; i < (int)coObjects->size(); i++)
			{
				switch (coObjects->at(i)->getID())
				{
				case ID_ENTITY_VAMPIRE_BAT:
				{
					VampireBat *vampireBat = dynamic_cast<VampireBat *>(coObjects->at(i));
					if (vampireBat->getName().compare(name) == 0)
					{
						vampireBat->SetState(VampireBat::VAMPIRE_STATE_HIDDEN);
					}
				}
				break;
				}
			}
		}
	}
}

ActivationBox::~ActivationBox()
{
}
