#pragma once
#include <string>
#include <windows.h>

std::wstring StringToLPCWSTR(const std::string &str);
std::string LPCWSTRToString(const std::wstring &wstr);
