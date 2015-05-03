#pragma once
#include "stdafx.h"
#include <windows.h>


namespace HookDLL
{
	

	class HookClass
	{
		const char *HOOK_DLL_NAME2 = "HookProcDLL.dll";
		static const int hookCount = 2;
		HMODULE dllHandle;
		std::vector<HHOOK> hooks;
	protected:
		int CheckHookProc(HOOKPROC proc, int ret);
		int CheckHook(HHOOK hook, int ret);
		void CleanupHooks(std::vector<HHOOK> hooks, size_t size);
		void CleanupLibraries();
	public:
		///<summary> Constructor, loads hook DLL and will report error. </summary>
		HookClass();
		HookClass(bool kbd, bool mse);
		~HookClass();
	};

}