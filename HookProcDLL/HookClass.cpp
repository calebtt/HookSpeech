#include "stdafx.h"
#include "HookClass.h"

namespace HookDLL
{

	//The error checking procedures take an integer that will help with debugging, it is only a temporary measure.
	HookClass::HookClass()
	{
		dllHandle = ::LoadLibrary(HOOK_DLL_NAME2);
		if(!dllHandle)
		{
			std::cerr << "Load Lib fail." << std::endl;
			throw std::exception("Load library failure.");
		}

		HOOKPROC keyProc = (HOOKPROC)::GetProcAddress(dllHandle, "keyboardHookProcedure");
		HOOKPROC proc = (HOOKPROC)::GetProcAddress(dllHandle, "mouseHookProcedure");
		int err = CheckHookProc(proc, 2);
		int err2 = CheckHookProc(keyProc, 3);

		if(err != 0 || err2 != 0)
		{
			//Cleanup
			CleanupLibraries();
			throw std::exception("Get proc addresses failure.");
		}


		std::cout << "Located mouse proc.\nSetting hook." << std::endl;
		hooks.push_back(::SetWindowsHookExA(WH_MOUSE_LL, proc, dllHandle, NULL));
		std::cout << "Located keyboard proc.\nSetting hook." << std::endl;
		hooks.push_back(::SetWindowsHookExA(WH_KEYBOARD_LL, keyProc, dllHandle, NULL));
	

		err = CheckHook(hooks[0], 3);
		err2 = CheckHook(hooks[1], 4);

		if(err != 0 || err2 != 0)
		{
			CleanupHooks(hooks, this->hookCount);
			CleanupLibraries();
			throw std::exception("Set hooks failure.");
		}

		std::cout << "\nAll hooks set.\n";
	}

	HookClass::HookClass(bool kbd, bool mse)
	{
		throw std::string("unfinished");
		dllHandle = NULL;
		dllHandle = ::LoadLibrary(HOOK_DLL_NAME);
		if(!dllHandle)
		{
			std::cerr << "Load Lib fail." << std::endl;
			throw std::exception("Load library failure.");
		}

		HOOKPROC keyProc = (HOOKPROC)::GetProcAddress(dllHandle, "keyboardHookProcedure");
		int err2 = CheckHookProc(keyProc, 3);
		if(err2 != 0)
		{
			//Cleanup
			CleanupLibraries();
			throw std::exception("Get proc addresses failure.");
		}
		std::cout << "Located keyboard proc.\nSetting hook." << std::endl;
		hooks.push_back(::SetWindowsHookExA(WH_KEYBOARD_LL, keyProc, dllHandle, NULL));

		HOOKPROC proc = (HOOKPROC)::GetProcAddress(dllHandle, "mouseHookProcedure");
		int err = CheckHookProc(proc, 2);


		std::cout << "Located mouse proc.\nSetting hook." << std::endl;
		hooks.push_back(::SetWindowsHookExA(WH_MOUSE_LL, proc, dllHandle, NULL));

	
		err = CheckHook(hooks[0], 3);
		err2 = CheckHook(hooks[1], 4);

		if(err != 0 || err2 != 0)
		{
			CleanupHooks(hooks, this->hookCount);
			CleanupLibraries();
			throw std::exception("Set hooks failure.");
		}

		std::cout << "\nAll hooks set.\n";
	}
	HookClass::~HookClass()
	{
		CleanupHooks(hooks,hookCount);
		CleanupLibraries();
	}

	int HookClass::CheckHookProc(HOOKPROC proc, int ret)
	{
		if(!proc)
		{
			std::cerr << "Last error: " << ::GetLastError() << std::endl;
			std::cerr << "Get proc addr fail." << std::endl;
			return ret;
		}
		return 0;
	}

	
	int HookClass::CheckHook(HHOOK hook, int ret)
	{
		if(!hook)
		{
			std::cerr << "Last error: " << ::GetLastError() << std::endl;
			std::cerr << "Set hook fail." << std::endl;
			return ret;
		}
		return 0;
	}
	void HookClass::CleanupHooks(std::vector<HHOOK> hooks, size_t size = hookCount)
	{
		BOOL ret = FALSE;
		for(size_t i = 0; i < size; i++)
		{
			ret = ::UnhookWindowsHookEx(hooks[i]);
			if(ret)
				std::cerr << "Hook unhooked." << std::endl;
			else
				std::cerr << "Hook ALREADY unhooked." << std::endl;
		}
	}
	void HookClass::CleanupLibraries()
	{
		FreeLibrary(dllHandle);
	}

}