#include "Grid.h"
#include "Direct3DManager.h"
#include <sstream>
#include <d3dx9.h>

Grid::Grid(int row, int col)
{
	this->row = row;
	this->col = col;
	staticObjects = new set<LPGAMEOBJECT>*[row];
	for (int i = 0; i < row; i++)
		staticObjects[i] = new set<LPGAMEOBJECT>[col];
}

void Grid::loadObjects(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			for (auto object : *coObjects)
			{
				if (!object->getCellId().empty() && object != nullptr)
				{
					for (int k = 0; k < object->getCellId().size(); k++)
					{
						D3DXVECTOR2 pos = object->getCellId()[k];
						if (pos.x == i && pos.y == j)
						{
							staticObjects[i][j].insert(object);
						}
					}
				}
			}
		}
	}
}

void Grid::updateObjects(vector<LPGAMEOBJECT>* coObjects)
{
	Viewport* viewPort = Direct3DManager::getInstance()->getViewport();

	int beginCol = viewPort->getX() / WIDTH_GRID;
	int endCol = (viewPort->getX() + viewPort->getWidth()) / WIDTH_GRID + 1;
	int beginRow = viewPort->getY() / HIEGHT_GRID;
	int endRow = (viewPort->getY() + viewPort->getHeight()) / HIEGHT_GRID + 1;

	beginCol = beginCol < 0 ? 0 : beginCol;
	endCol = endCol > col ? col : endCol;
	beginRow = beginRow < 0 ? 0 : beginRow;
	endRow = endRow > row ? row : endRow;

	set<LPGAMEOBJECT> unduplicateObjects;

	for (int i = beginRow; i < endRow; i++)
		for (int j = beginCol; j < endCol; j++)
			for (auto object : staticObjects[i][j])
			{
				if (object != nullptr 
					&&object->GetState()!= GameObject::STATE_DETROY)
				{
					if (unduplicateObjects.insert(object).second)
					{
						coObjects->push_back(object);
					}
				}
			}
}

void Grid::update(vector<LPGAMEOBJECT>* coObjects)
{
	dynamicObjects.clear();
	for (int i = 0; i < (int)coObjects->size(); i++)
	{
		switch (coObjects->at(i)->getID())
		{
		case ID_ENTITY_FLOOR:
			break;
		case ID_ENTITY_DOOR:
			break;
		case ID_ENTITY_BRICK:
			break;
		case ID_ENTITY_BURNBARREL:
			break;
		case ID_ENTITY_ENTRANCE:
			break;
		case ID_ENTITY_WALL:
			break;
		case ID_ENTITY_CANDLE:
			break;
		case ID_ENTITY_FISH_MAN:
			break;
		case ID_ENTITY_CASTLEVANIA_WALL:
			break;
		case ID_ENTITY_STAIR:
			break;
		case ID_ENTITY_PANTHER:
			break;
		case ID_ENTITY_DARK_BAT:
			break;
		case ID_ENTITY_MOVING_MAP:
			break;
		case ID_ENTITY_SPAWN_ENEMY:
			break;
		default:
			dynamicObjects.insert(coObjects->at(i));
			break;
		}
	}
	coObjects->clear();
	updateObjects(coObjects);
	for (auto object : dynamicObjects)
	{
		coObjects->push_back(object);
	}
}

Grid::~Grid()
{
}
