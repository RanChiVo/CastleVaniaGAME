#include "ObjectGridCreation.h"
#include <d3dx9.h>
#include <sstream>
#include <set> 
#include "Grid.h"

ObjectGridCreation::ObjectGridCreation(std::string resourcepath)
{
	this->resourcepath = resourcepath;
}

void  ObjectGridCreation::divideOnjectToGrid(vector<LPGAMEOBJECT>* objects, int row, int col)
{
	for (auto object : *objects)
	{
		float ol, ot, or , ob, gl, gt, gr, gb;

		object->GetBoundingBox(ol, ot, or , ob);

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				gl = j * HIEGHT_GRID;
				gr = (j + 1) * HIEGHT_GRID;
				gt = i * WIDTH_GRID;
				gb = (i + 1) * WIDTH_GRID;
				
				if (object->checkCollision({ (long)ol, (long)ot, (long) or , (long)ob },
					{ (long)gl, (long)gt, (long)gr, (long)gb }))
				{
					addPropetiesToFile(object->getMainId(), std::to_string(i) +","+ std::to_string(j));
				}
			}
	}
}

void ObjectGridCreation::checkGoodFile()
{
	this->isGoodFile = doc.load_file(resourcepath.c_str());
	if (!isGoodFile)
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
		return;
	}
	this->rootNode = doc.child("map");
}

void ObjectGridCreation::addPropetiesToFile(int mainId, std::string cellId)
{
	checkGoodFile();

	for (auto objectGroupNode : rootNode.children("objectgroup"))
	{
		for (auto objectNode : objectGroupNode.children("object"))
		{
			int id = objectNode.attribute("id").as_int();

			auto properties = objectNode.child("properties");

			if (id == mainId)
			{
				for (auto propertyNode : properties)
				{
					std::string nameProperty = propertyNode.attribute("name").as_string();
					if (nameProperty.compare("Cell ID") == 0)
					{
						std::string currentCellId = propertyNode.attribute("value").as_string();

						if (currentCellId.empty())
						{
							propertyNode.attribute("value")
								.set_value(cellId.c_str());
						}
						else propertyNode.attribute("value")
							.set_value((currentCellId+" "+ cellId).c_str());
					}
				}
			}
		}
	}
	
	bool saveSucceeded = doc.save_file(resourcepath.c_str(), PUGIXML_TEXT("  "));
}

ObjectGridCreation::~ObjectGridCreation()
{
}
