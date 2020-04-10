#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <sstream>

void eraseAllSubStr(std::string & mainStr, const std::string & toErase);

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr);
