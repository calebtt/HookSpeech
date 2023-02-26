// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
// Exclude rarely-used stuff from Windows headers
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// Windows Header Files
#include <Windows.h>
// Standard lib includes
#include <iostream>
#include <vector>
#include <string>
#include <concepts>
#include <bitset>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
#include <atomic>
#include <mutex>
#include <unordered_map>
// Files I want to make sure are compiled into the DLL
#include "apifuncs.h"
