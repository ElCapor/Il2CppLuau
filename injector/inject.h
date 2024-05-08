#pragma once
// #define USE_MANUAL_MAP

#include <Windows.h>
#include <string>
#include "load-library.h"
#ifdef USE_MANUAL_MAP
#include "manual-map.h"
#endif

enum class InjectionType
{
	LoadLibraryDLL,
	ManualMap
};

void Inject(HANDLE hProcess, const std::string& dllPath, InjectionType type = InjectionType::LoadLibraryDLL);