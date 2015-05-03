// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HOOKPROCDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HOOKPROCDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HOOKPROCDLL_EXPORTS
#define HOOKPROCDLL_API __declspec(dllexport)
#else
#define HOOKPROCDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus    // If used by C++ code, 
extern "C" 
{          // we need to export the C interface
#endif

HOOKPROCDLL_API LRESULT mouseHookProcedure(int code, WPARAM wParam, LPARAM lParam);
HOOKPROCDLL_API LRESULT keyboardHookProcedure(int code, WPARAM wParam, LPARAM lParam);
HOOKPROCDLL_API bool SetTranslationAlphabet(std::wstring str);

#ifdef __cplusplus
}
#endif

HHOOK hHook = 0;
sds::SendKey sender;
static bool isShiftDown = false;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//hHook = ::SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)keyboardHookProcedure, NULL, NULL);
		//if(hHook == NULL)
			//MessageBox(NULL, "Sethook fail", "", MB_OK);
		//break;
	case DLL_THREAD_ATTACH:

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//UnhookWindowsHookEx(hHook);
		break;
	}
	return TRUE;
}

//Can be used in the future, a mouse hook procedure.
HOOKPROCDLL_API LRESULT mouseHookProcedure(int code, WPARAM wParam, LPARAM lParam)
{
	if(code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);
	if(code == HC_ACTION)
	{
		//Do stuff here.
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

//The low level keyboard hook procedure.
HOOKPROCDLL_API LRESULT keyboardHookProcedure(int code, WPARAM wParam, LPARAM lParam)
{
	if(code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);
	
	if(code == HC_ACTION)
	{
		//Retrieve information from keyboard hook structure.
		PKBDLLHOOKSTRUCT kb = (PKBDLLHOOKSTRUCT)lParam;
		

		if (wParam == WM_KEYDOWN)
		{
			//If highest order bit is set, key is down. SHORT is 2 bytes in length on this, and most machines.
			isShiftDown = (GetKeyState(VK_SHIFT) & 0x1000000000000000);

			//Determine if a part of the working character set.
			if (sender.IsWorkingSetCharacter(static_cast<char>(kb->vkCode)))
			{
				if (isShiftDown)
					sender.SendUnicode((kb->vkCode), true);
				else
					sender.SendUnicode(tolower(kb->vkCode), true);
				return 1; // Mark input as handled by this hook.	
			}
		}
		else if (wParam == WM_KEYUP)
		{
			if (sender.IsWorkingSetCharacter(static_cast<char>(kb->vkCode)))
			{
				if (isShiftDown)
					sender.SendUnicode((kb->vkCode), false);
				else
					sender.SendUnicode(tolower(kb->vkCode), false);
				return 1;
			}
		}
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

//Updates the alphabet used for translation.
HOOKPROCDLL_API bool SetTranslationAlphabet(std::wstring str)
{
	return sender.UpdateTranslationAlphabet(str);
}