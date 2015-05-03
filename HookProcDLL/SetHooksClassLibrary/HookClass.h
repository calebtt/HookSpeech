//Caleb Taylor 2015

#pragma once
#include "stdafx.h"
#include <windows.h>


namespace HookDLL
{
	class HookClass
	{
		//AlphabetUpdateFunc is a typedef for a function pointer with the return type and parameters that match the function in the DLL.
		//We will use this to store the address of the DLL function, and call it.
		typedef bool(__stdcall *AlphabetUpdateFunc)(std::wstring str);
		AlphabetUpdateFunc updateFunction;

		const char *HookDllName = "HookProcDLL.dll";

		//Not used.
		const char *KeyboardHookProcedureName = "keyboardHookProcedure";
		const char *AlphabetUpdateProcedureName = "SetTranslationAlphabet";

		//Handle to a loaded DLL.
		HMODULE dllHandle;

		//hook procedure handles.
		HOOKPROC keyProc;
		HOOKPROC mouseProc;

		//Handle to an already set Windows hook.
		HHOOK keyboardHookHandle;

		//Enabled status.
		bool m_enabled;

	protected:
		//Tests a HOOKPROC structure for error condition.
		bool CheckHookProc(HOOKPROC proc);
		//Tests a HHOOK structure for error condition.
		bool CheckHook(HHOOK hook);
		//Tests a HMODULE handle to the DLL for error condition.
		bool CheckDllHandle(HMODULE hDll);
		//Remove windows hooks.
		void CleanupHooks();
		//Free DLL.
		void CleanupLibraries();
		//Loads a DLL, the handle is obtained via handleToDll.
		bool LoadDLL(HMODULE &handleToDll);
		//Obtains the address of the specified procedure in the specified DLL.
		bool GetFunctionLocationInDll(HMODULE handleToLoadedDll, HOOKPROC &hookProc);
		bool GetAlphabetUpdateFunctionInDll(HMODULE handleToLoadedDll, AlphabetUpdateFunc &f);
	public:
		//Default constructor.
		HookClass();
		//Default destructor.
		~HookClass();
		
		//Used to toggle the keyboard hook.
		void Toggle();

		//Used to update the translation alphabet.
		bool UpdateTranslation(std::wstring update);
	};

}