// HookProc DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HookProcDLL.h"


HOOKPROCDLL_API LRESULT hookProcedure(int code, WPARAM wParam, LPARAM lParam)
{
	MSLLHOOKSTRUCT *s = (MSLLHOOKSTRUCT*)lParam;
	s->flags &= LLMHF_INJECTED; 

	return CallNextHookEx(NULL, code, wParam, lParam);
}
