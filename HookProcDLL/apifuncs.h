#pragma once
#include "stdafx.h"
#include "SendAlphabet.h"

extern "C"
{
	namespace StaticInstance
	{
		using LockType = std::scoped_lock <std::mutex>;
		inline static std::mutex locker;
		inline static sds::SendAlphabet sender;
		inline static std::string workingAlphabetChars;
		inline static std::wstring translationAlphabetChars;
		inline static std::atomic<HHOOK> hookHandle{ nullptr };
		inline static constexpr std::size_t SZ_MODULE_NAME{ 512 };
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
		StaticInstance::LockType tempLock(StaticInstance::locker);
		StaticInstance::translationAlphabetChars = std::wstring(str);
		return StaticInstance::sender.UpdateTranslationAlphabet(StaticInstance::translationAlphabetChars);
	}
	__declspec(dllexport) inline bool SetWorkingAlphabet(const char *str)
	{
		StaticInstance::LockType tempLock(StaticInstance::locker);
		StaticInstance::workingAlphabetChars = std::string(str);
		return StaticInstance::sender.UpdateWorkingAlphabet(StaticInstance::workingAlphabetChars);
	}
	__declspec(dllexport) inline const wchar_t* GetTranslationAlphabet()
	{
		StaticInstance::LockType tempLock(StaticInstance::locker);
		StaticInstance::translationAlphabetChars = StaticInstance::sender.GetTranslationAlphabet();
		return StaticInstance::translationAlphabetChars.c_str();
	}
	__declspec(dllexport) inline const char* GetWorkingAlphabet()
	{
		StaticInstance::LockType tempLock(StaticInstance::locker);
		StaticInstance::workingAlphabetChars = StaticInstance::sender.GetWorkingAlphabet();
		return StaticInstance::workingAlphabetChars.c_str();
	}
	__declspec(dllexport) inline bool IsHooked()
	{
		StaticInstance::LockType tempLock(StaticInstance::locker);
		return StaticInstance::hookHandle;
	}
	__declspec(dllexport) inline bool AddHooks()
	{
		StaticInstance::LockType tempLock(StaticInstance::locker);
		if (!StaticInstance::hookHandle)
		{
			char moduleName[StaticInstance::SZ_MODULE_NAME]{};
			const DWORD readChars = GetModuleFileNameA(nullptr, moduleName, StaticInstance::SZ_MODULE_NAME); // if it won't fit, it only tries to put SZ_MODULE_NAME chars.
			if(readChars < StaticInstance::SZ_MODULE_NAME)
				StaticInstance::hookHandle = ::SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHookProcedure, GetModuleHandleA(moduleName), NULL);
		}
		return StaticInstance::hookHandle != nullptr;
	}
	__declspec(dllexport) inline bool RemoveHooks()
	{
		//From Winapi docs, it's more of a fire and forget because it can be in the state of processing
		//a key event and not unhook immediately.
		StaticInstance::LockType tempLock(StaticInstance::locker);
		::UnhookWindowsHookEx(StaticInstance::hookHandle);
		StaticInstance::hookHandle = nullptr;
		return true;
	}
	//Can be used in the future, a mouse hook procedure.
	inline LRESULT mouseHookProcedure(int code, WPARAM wParam, LPARAM lParam)
	{
		if (code < 0)
			return CallNextHookEx(nullptr, code, wParam, lParam);
		if (code == HC_ACTION)
		{
			//Do stuff here.
		}

		return CallNextHookEx(nullptr, code, wParam, lParam);
	}
	//The low level keyboard hook procedure.
	inline LRESULT keyboardHookProcedure(int code, WPARAM wParam, LPARAM lParam)
	{
		if (code < 0)
			return CallNextHookEx(nullptr, code, wParam, lParam);
		if (code == HC_ACTION)
		{
			//Retrieve information from keyboard hook structure.
			const auto* kb = (PKBDLLHOOKSTRUCT)lParam;
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
		return CallNextHookEx(nullptr, code, wParam, lParam);
	}
}
