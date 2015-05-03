// Caleb Taylor 2015
// Small helper class for simulating input and doing the translation to the new alphabet.
// Used in the DLLmain function.


#pragma once
#include "stdafx.h"

namespace sds
{
	class SendKey
	{
		//The INPUT structure is used by the Windows API function "SendInput()".
		INPUT keyInput;
		std::string workingAlphabet;
		std::wstring newAlphabet;

	public:
		//Constructor
		SendKey()
		{
			//Initialize our working alphabet.
			this->workingAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			this->newAlphabet = L"àƀćďĕƒğħíĵĸlmnǒpqrƨţuvwxÿzĀßCĐEFĢĦIJƘŁMNOƤQRƧŦUVWXYZ";
			//this->newAlphabet = L"4bcd3fgh1jklmn0pqr57uvwxyz4bcd3fgh1jklmn0pqr57uvwxyz";

			memset(&keyInput,0,sizeof(INPUT));
			keyInput.type = INPUT_KEYBOARD;
		}
		//Simulates a hardware key-press for non-unicode characters.
		void Send(int vk, bool down)
		{
			WORD scanCode = GetScanCode(vk);
			char vkCharacter = (char)vk;

			//Find character in alphabet.
			size_t ind = this->workingAlphabet.find(vkCharacter);
			//If couldn't find it...
			if (ind == std::string::npos)
			{
				return;
			}
			scanCode = GetScanCode(this->newAlphabet.at(ind));



			//Filling in the sendinput structure.
			//keyInput.ki.wVk = this->newAlphabet.at(ind);
			keyInput.ki.wScan = scanCode; 
			keyInput.ki.dwExtraInfo = GetMessageExtraInfo();
			keyInput.ki.dwFlags = KEYEVENTF_SCANCODE ;


			//Character is in the "KEY DOWN" state already, and the request is to send keyup.
			if (!down)
			{
				//Character is in the "KEY DOWN" state already.
				keyInput.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
			}

			UINT ret = SendInput(1,&keyInput,sizeof(INPUT));
			if (ret == 0)
			{
				throw std::exception("SendInput failed to send the input.");
			}
			//assert(ret != 0);
		}
		//Sends a simulated key-press for unicode characters.
		void SendUnicode(int vk, bool down)
		{
			WORD scanCode = GetScanCode(vk);
			char vkCharacter = (char)vk;

			//Find character in alphabet.
			size_t ind = this->workingAlphabet.find(vkCharacter);
			//If couldn't find it...
			if (ind == std::string::npos)
			{
				return;
			}

			//Filling in the sendinput structure.
			keyInput.ki.wScan = this->newAlphabet.at(ind);
			keyInput.ki.dwExtraInfo = GetMessageExtraInfo();
			keyInput.ki.dwFlags = KEYEVENTF_UNICODE;

			//Character is in the "KEY DOWN" state already, and the request is to send keyup.
			if (!down)
			{
				//Character is in the "KEY DOWN" state already.
				keyInput.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
			}


			UINT ret = SendInput(1, &keyInput, sizeof(INPUT));

			if (ret == 0)
			{
				throw std::exception("SendInput failed to send the input.");
			}
		}
		
		//Determines if "int vk" is in the working alphabet, this is the english alphabet a-z and A-Z.
		//Returns: true if character is in working alphabet, false otherwise.
		bool IsWorkingSetCharacter(int vk)
		{
			char c = (char)vk;
			return (this->workingAlphabet.find(c) != std::string::npos);
		}
		
		//Updates the alphabet the English characters are translated to.
		//Note: The new alphabet "wstring update" needs to be the same length as the internal workingAlphabet.
		//Returns: false on update failure, true on success.
		bool UpdateTranslationAlphabet(std::wstring update)
		{
			if (this->workingAlphabet.size() != update.size())
				return false;
			this->newAlphabet = update;
			return true;

		}
		size_t GetWorkingAlphabetSize() const
		{
			return this->workingAlphabet.size();
		}
	private:
		//Gets the virtual scan code (VSC) for a virtual key (VK).
		WORD GetScanCode(int vk)
		{
			WORD ret =
				(MapVirtualKeyExA(VkKeyScanA(vk), MAPVK_VK_TO_VSC,GetKeyboardLayout(NULL)));
			if( ret == 0 )
				ret = static_cast<WORD> (MapVirtualKeyExA(vk, MAPVK_VK_TO_VSC,GetKeyboardLayout(NULL)));
			
			return ret;
		}
	};
}