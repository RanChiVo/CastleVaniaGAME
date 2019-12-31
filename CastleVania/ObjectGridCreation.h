#pragma once
#include "GameObjects/GameObject.h"
#include "Library/pugixml.hpp"

class ObjectGridCreation
{
private:
	pugi::xml_document doc;
	pugi::xml_node rootNode;
	pugi::xml_parse_result isGoodFile;
	std::string resourcepath;
public:
	ObjectGridCreation(std::string resourcepath);
	void divideOnjectToGrid(vector<LPGAMEOBJECT>* objects, int row, int col);
	void checkGoodFile();
	void addPropetiesToFile(int mainId, std::string cellId);
	~ObjectGridCreation();
};

