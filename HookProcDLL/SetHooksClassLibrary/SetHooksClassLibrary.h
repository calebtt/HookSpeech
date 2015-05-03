// SetHooksClassLibrary.h
// Caleb Taylor 2015
// If you use this code elsewhere, please mention me somewhere in the app.


#pragma once

#using <mscorlib.dll>

#include <windows.h>

#include <atlstr.h>

#include <msclr\marshal.h>
#include "msclr\marshal_cppstd.h"

using namespace msclr::interop;

using namespace System;

using namespace System::IO;

using namespace System::Collections;

using namespace System::Collections::Specialized;


#include "HookClass.h"

namespace SetHooksClassLibrary 
{

	//Our wrapper class that wraps the native DLL loading and hook setting class.
	public ref class HooksWrapper
	{
		//Native pointer to our native DLL manager class.
		HookDLL::HookClass *hcp;
	public:
		//Constructor, will throw an exception if there is a problem instantiating the native class instance.
		HooksWrapper()
		{
			try
			{
				hcp = new HookDLL::HookClass();
			}
			catch (const std::exception& ex)
			{
				throw gcnew Exception(gcnew System::String(ex.what()));
			}
		}
		//Destructor, deletes the native class instance.
		~HooksWrapper()
		{
			delete hcp;
		}

		//Toggles the windows hook on/off.
		//When toggled off, the keyboard keys will not be replaced with the translation alphabet.
		void Toggle()
		{
			try
			{
				hcp->Toggle();
			}
			catch (const std::exception& ex)
			{
				throw gcnew Exception(gcnew System::String(ex.what()));
			}
		}

		//Pass some data on to the native class. This updates the translation alphabet, currently "àƀćďĕƒğħíĵĸlmnǒpqrƨţuvwxÿzĀßCĐEFĢĦIJƘŁMNOƤQRƧŦUVWXYZ"
		//String update should be 52 characters in length, or the same length as the alphabet to be translated.
		//In this case the english alphabet used is "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".
		//Returns: false on failure, true on success.
		//Note: Unicode or otherwise "wide" characters are what this is intended to be used with.
		bool UpdateAlphabet(System::String ^update)
		{
			//marshal_as is quite useful.
			std::wstring wsout = msclr::interop::marshal_as<std::wstring>(update);
			return hcp->UpdateTranslation(wsout);
		}
	};
}
