#pragma once
#include "stdafx.h"
namespace sds::Utilities
{
	/// <summary>Utility class for simulating input via Windows API.</summary>
	class SendKeyInput
	{
	public:
		/// <summary>Sends the virtual keycode as a unicode keypress.</summary>
		/// <param name="vk"> is the Virtual Keycode of the keystroke you wish to emulate </param>
		/// <param name="down"> is a boolean denoting if the keypress event is KEYDOWN or KEYUP</param>
		static void SendUnicode(const int vk, const bool down) noexcept
		{
			INPUT tempInput{};
			if(vk)
			{
				//do scancode
				tempInput = {};
				tempInput.type = INPUT_KEYBOARD;
				if (down)
					tempInput.ki.dwFlags = KEYEVENTF_UNICODE;
				else
					tempInput.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
				tempInput.ki.wScan = static_cast<WORD>(vk);
				const UINT ret = CallSendInput(&tempInput, 1);
				if (ret == 0)
					LogError("SendInput failed.");
			}
		}
		/// <summary>One member function calls SendInput with the eventual built INPUT struct.
		/// This is useful for debugging or re-routing the output for logging/testing of a real-time system.</summary>
		/// <param name="inp">Pointer to first element of INPUT array.</param>
		/// <param name="numSent">Number of elements in the array to send.</param>
		static UINT CallSendInput(INPUT* inp, const size_t numSent) noexcept
		{
			return SendInput(static_cast<UINT>(numSent), inp, sizeof(INPUT));
		}
	private:
		static void LogError(std::string err) noexcept
		{
			//std::cerr << err << std::endl;
		}
	};
}