#pragma once
#include "stdafx.h"
#include "SendAlphabet.h"
#include <fstream>
extern "C"
{
	namespace StaticInstance
	{
		inline static sds::SendAlphabet sender;
		inline static std::string workingAlphabetChars;
		inline static std::wstring translationAlphabetChars;
		inline static HHOOK hookHandle = NULL;
		inline static constexpr size_t SZ_MODULE_NAME = 512;
	}
	// Forward declarations section.
	__declspec(dllexport) inline bool SetTranslationAlphabet(const wchar_t *str);
	__declspec(dllexport) inline bool SetWorkingAlphabet(const char *str);
	__declspec(dllexport) inline const wchar_t* GetTranslationAlphabet();
	__declspec(dllexport) inline const char* GetWorkingAlphabet();
	__declspec(dllexport) inline bool IsHooked();
	__declspec(dllexport) inline bool AddHooks();
	__declspec(dllexport) inline bool RemoveHooks();
	inline LRESULT mouseHookProcedure(int code, WPARAM wParam, LPARAM lParam);
	inline LRESULT keyboardHookProcedure(int code, WPARAM wParam, LPARAM lParam);
	// Exported Interface Section.
	__declspec(dllexport) inline bool SetTranslationAlphabet(const wchar_t *str)
	{
		StaticInstance::translationAlphabetChars = std::wstring(str);
		return StaticInstance::sender.UpdateTranslationAlphabet(StaticInstance::translationAlphabetChars);
	}
	__declspec(dllexport) inline bool SetWorkingAlphabet(const char *str)
	{
		StaticInstance::workingAlphabetChars = std::string(str);
		return StaticInstance::sender.UpdateWorkingAlphabet(StaticInstance::workingAlphabetChars);
	}
	__declspec(dllexport) inline const wchar_t* GetTranslationAlphabet()
	{
		// returning address of static instance data, copy it where used.
		StaticInstance::translationAlphabetChars = StaticInstance::sender.GetTranslationAlphabet();
		return StaticInstance::translationAlphabetChars.c_str();
	}
	__declspec(dllexport) inline const char* GetWorkingAlphabet()
	{
		// returning address of static instance data, copy it where used.
		StaticInstance::workingAlphabetChars = StaticInstance::sender.GetWorkingAlphabet();
		return StaticInstance::workingAlphabetChars.c_str();
	}
	__declspec(dllexport) inline bool IsHooked()
	{
		return StaticInstance::hookHandle;
	}
	__declspec(dllexport) inline bool AddHooks()
	{
		if (!StaticInstance::hookHandle)
		{
			char moduleName[StaticInstance::SZ_MODULE_NAME]{};
			const DWORD readChars = GetModuleFileNameA(NULL, moduleName, StaticInstance::SZ_MODULE_NAME); // if it won't fit, it only tries to put SZ_MODULE_NAME chars.
			if(readChars < StaticInstance::SZ_MODULE_NAME)
				StaticInstance::hookHandle = ::SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHookProcedure, GetModuleHandleA(moduleName), NULL);
		}
		return StaticInstance::hookHandle != NULL;
	}
	__declspec(dllexport) inline bool RemoveHooks()
	{
		BOOL res = ::UnhookWindowsHookEx(StaticInstance::hookHandle);
		if (res)
			StaticInstance::hookHandle = NULL;
		return res;
	}
	//Can be used in the future, a mouse hook procedure.
	inline LRESULT mouseHookProcedure(int code, WPARAM wParam, LPARAM lParam)
	{
		if (code < 0)
			return CallNextHookEx(NULL, code, wParam, lParam);
		if (code == HC_ACTION)
		{
			//Do stuff here.
		}

		return CallNextHookEx(NULL, code, wParam, lParam);
	}
	//The low level keyboard hook procedure.
	inline LRESULT keyboardHookProcedure(int code, WPARAM wParam, LPARAM lParam)
	{
		if (code < 0)
			return CallNextHookEx(NULL, code, wParam, lParam);
		if (code == HC_ACTION)
		{
			//Retrieve information from keyboard hook structure.
			const PKBDLLHOOKSTRUCT kb = (PKBDLLHOOKSTRUCT)lParam;
			const wchar_t translated = StaticInstance::sender.IsTranslatable(static_cast<int>(kb->vkCode));
			if (translated)
			{
				if (wParam == WM_KEYDOWN)
				{
					StaticInstance::sender.Send(translated, true);
					return 1; // Mark input as handled by this hook.
				}
				else if (wParam == WM_KEYUP)
				{
					StaticInstance::sender.Send(translated, false);
					return 1;
				}
			}
		}
		return CallNextHookEx(NULL, code, wParam, lParam);
	}
}