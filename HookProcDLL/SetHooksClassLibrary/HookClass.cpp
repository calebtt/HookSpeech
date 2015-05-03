#pragma once
#include "stdafx.h"
#include "HookClass.h"

namespace HookDLL
{

	//Throws exceptions if there is any problem loading the DLL or finding the hook procedures.
	HookClass::HookClass() : m_enabled(true)
	{
		//Load library, check for error.
		if (!this->LoadDLL(this->dllHandle))
		{
			std::cerr << "Load Lib fail." << std::endl;
			throw std::exception("Load library failure.");
		}

		//Get address of our keyboard hook procedure in the DLL we just loaded, and check for error.
		if (!GetFunctionLocationInDll(this->dllHandle, this->keyProc))
		{
			//Handle error.
			CleanupLibraries();
			throw std::exception("Failed to acquire handle to keyboard hook procedure!");
		}
		//Get address of our update string function in the DLL.
		if (!this->GetAlphabetUpdateFunctionInDll(this->dllHandle, this->updateFunction))
		{
			//Handle error.
			CleanupLibraries();
			throw std::exception("Failed to acquire handle to alphabet update procedure!");
		}
		

		//Set hooks, finally.
		std::cout << "Located keyboard proc.\nAttempting to set hook." << std::endl;
		this->keyboardHookHandle = ::SetWindowsHookExA(WH_KEYBOARD_LL, this->keyProc, this->dllHandle, NULL);

		//Check the hook procedures for error state before continuing.
		if (!this->CheckHook(this->keyboardHookHandle))
		{
			//Handle error.
			this->CleanupHooks();
			this->CleanupLibraries();
			std::cerr << "Unexpected error. Hook handles are invalid." << std::endl;
			throw std::exception("Unexpected error. Hook handles are invalid.");
		}

		std::cout << "\nAll hooks set.\n";
	}
	HookClass::~HookClass()
	{
		CleanupHooks();
		CleanupLibraries();
	}

	//Tests a hook procedure HOOKPROC for error status.
	//Returns: false on error detected.
	bool HookClass::CheckHookProc(HOOKPROC proc)
	{
		if(!proc)
		{
			std::cerr << "Last error: " << ::GetLastError() << std::endl;
			std::cerr << "Get proc addr fail." << std::endl;
			return false;
		}
		return true;
	}
	//Tests a HHOOK for error status.
	//Returns: false on error detected.
	bool HookClass::CheckHook(HHOOK hook)
	{
		if(!hook)
		{
			std::cerr << "Last error: " << ::GetLastError() << std::endl;
			std::cerr << "Set hook fail." << std::endl;
			return false;
		}
		return true;
	}
	bool HookClass::CheckDllHandle(HMODULE hDll)
	{
		return (bool)this->dllHandle;
	}

	void HookClass::CleanupHooks()
	{
		::UnhookWindowsHookEx(this->keyboardHookHandle);
	}
	void HookClass::CleanupLibraries()
	{
		FreeLibrary(dllHandle);
	}



	//Loads the DLL specified by HOOK_DLL_NAME
	//Returns: True on success, false on failure.
	bool HookClass::LoadDLL(HMODULE &handleToDll)
	{
		//Load library, check for error.
		handleToDll = ::LoadLibraryA(HookDllName);

		//True on success, false on failure.
		return (bool)handleToDll;

	}

	bool HookClass::GetFunctionLocationInDll(HMODULE handleToLoadedDll, HOOKPROC &hookProc)
	{
		//hookProc = (HOOKPROC)::GetProcAddress(handleToLoadedDll, MAKEINTRESOURCEA(2));
		hookProc = (HOOKPROC)::GetProcAddress(handleToLoadedDll, this->KeyboardHookProcedureName);
		return CheckHookProc(hookProc);
		
	}

	bool HookClass::GetAlphabetUpdateFunctionInDll(HMODULE handleToLoadedDll, AlphabetUpdateFunc &f)
	{
		//AlphabetUpdateFunc is a typedef for a function pointer with the return type and parameters that match the function in the DLL.
		//f = (AlphabetUpdateFunc)::GetProcAddress(handleToLoadedDll, MAKEINTRESOURCEA(1));
		f = (AlphabetUpdateFunc)::GetProcAddress(handleToLoadedDll, this->AlphabetUpdateProcedureName);
		return f != NULL;
	}

	//Used to toggle the keyboard hook.
	void HookClass::Toggle()
	{
		if (m_enabled)
		{
			//Disable it.
			this->CleanupHooks();
			m_enabled = false;
		}
		else
		{
			//Enable it.
			this->keyboardHookHandle = ::SetWindowsHookExA(WH_KEYBOARD_LL, this->keyProc, this->dllHandle, NULL);
			m_enabled = true;
		}
	}
	//Used to update the translation alphabet.
	bool HookClass::UpdateTranslation(std::wstring update)
	{
		return updateFunction(update);
	}
}