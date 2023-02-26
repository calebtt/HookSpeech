#pragma once
#include "stdafx.h"
namespace sds::Utilities
{
	/// <summary>Utility class for simulating input via Windows API.</summary>
	class SendKeyInput
	{
		using ScanMapType = std::map<int, int>;
		using ScanCodeType = unsigned short;
		using VirtualKeyType = unsigned int;
		using PrintableType = char;
		using VkType = unsigned char;
	public:
		//Turn auto disable numlock on or off
		inline static bool m_auto_disable_numlock{ true }; // toggle this to make the default behavior not toggle off numlock on your keyboard
		//Memoized scancode translations, doesn't need to be done again at runtime if done once before.
		inline static ScanMapType m_scancode_store{};
	public:
		/// <summary>Default Constructor</summary>
		SendKeyInput() = delete;
		SendKeyInput(const SendKeyInput& other) = delete;
		SendKeyInput(SendKeyInput&& other) = delete;
		SendKeyInput& operator=(const SendKeyInput& other) = delete;
		SendKeyInput& operator=(SendKeyInput&& other) = delete;
		~SendKeyInput() = delete;
		/// <summary>Sends the virtual keycode as a hardware scancode.</summary>
		/// <param name="vk"> is the Virtual Keycode of the keystroke you wish to emulate </param>
		/// <param name="down"> is a boolean denoting if the keypress event is KEYDOWN or KEYUP</param>
		static void SendScanCodeAscii(const int vk, const bool down) noexcept
		{
			if (m_auto_disable_numlock)
			{
				UnsetNumlockAsyncAscii();
			}
			INPUT tempInput = {};
			auto MakeItMouse = [&tempInput](const DWORD flagsDown, const DWORD flagsUp, const bool isDown)
			{
				tempInput.type = INPUT_MOUSE;
				if (isDown)
					tempInput.mi.dwFlags = flagsDown;
				else
					tempInput.mi.dwFlags = flagsUp;
				tempInput.mi.dwExtraInfo = GetMessageExtraInfo();
				CallSendInput(&tempInput, 1);
			};
			const WORD scanCode = GetScanCode(vk);
			if (scanCode == 0)
			{
				//try mouse
				switch (vk)
				{
				case VK_LBUTTON:
					MakeItMouse(MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, down); break;
				case VK_RBUTTON:
					MakeItMouse(MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, down); break;
				case VK_MBUTTON:
					MakeItMouse(MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP, down); break;
				case VK_XBUTTON1: [[fallthrough]];
				case VK_XBUTTON2:
					MakeItMouse(MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP, down); break;
				default: break;
				}
			}
			else
			{
				//do scancode
				tempInput = {};
				tempInput.type = INPUT_KEYBOARD;
				if (down)
					tempInput.ki.dwFlags = KEYEVENTF_SCANCODE;
				else
					tempInput.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
				tempInput.ki.wScan = scanCode;
				const UINT ret = CallSendInput(&tempInput, 1);
				if (ret == 0)
					LogError("SendInput returned 0 in SendScanCodeAscii(...)");
			}
		}
		/// <summary>Sends the virtual keycode as a unicode keypress.</summary>
		/// <param name="vk"> is the Virtual Keycode of the keystroke you wish to emulate </param>
		/// <param name="down"> is a boolean denoting if the keypress event is KEYDOWN or KEYUP</param>
		static void SendVirtualKeyUnicode(const int vk, const bool down) noexcept
		{
			INPUT tempInput{};
			if (vk)
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
					LogError("SendInput failed in SendVirtualKeyUnicode(...)");
			}
		}
		/// <summary>Utility function to send a virtual keycode as input to the OS.
		///	Handles keyboard keys and several mouse click buttons.</summary>
		static UINT SendVirtualKeyAscii(const VirtualKeyType vk, const bool isKeyboard, const bool sendDown) noexcept
		{
			INPUT inp{};
			inp.type = isKeyboard ? INPUT_KEYBOARD : INPUT_MOUSE;
			if (isKeyboard)
			{
				inp.ki.dwFlags = sendDown ? 0 : KEYEVENTF_KEYUP;
				inp.ki.wVk = static_cast<WORD>(vk);
				inp.ki.dwExtraInfo = GetMessageExtraInfo();
			}
			else
			{
				switch (vk)
				{
				case VK_LBUTTON:
					inp.mi.dwFlags = sendDown ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP; break;
				case VK_RBUTTON:
					inp.mi.dwFlags = sendDown ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP; break;
				case VK_MBUTTON:
					inp.mi.dwFlags = sendDown ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP; break;
				case VK_XBUTTON1: [[fallthrough]]; //annotated fallthrough
				case VK_XBUTTON2:
					inp.mi.dwFlags = sendDown ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP; break;
				default:
					return 0;
				}
				inp.mi.dwExtraInfo = GetMessageExtraInfo();
			}
			return CallSendInput(&inp, 1);
		}
	private:
		/// <summary>One member function calls SendInput with the eventual built INPUT struct.
		/// This is useful for debugging or re-routing the output for logging/testing of a real-time system.</summary>
		/// <param name="inp">Pointer to first element of INPUT array.</param>
		/// <param name="numSent">Number of elements in the array to send.</param>
		static UINT CallSendInput(INPUT* inp, const size_t numSent) noexcept
		{
			return SendInput(static_cast<UINT>(numSent), inp, sizeof(INPUT));
		}
		static void LogError(std::string err) noexcept
		{
			//std::cerr << err << std::endl;
		}
		/// <summary>Called to asynchronously unset the numlock key, if set.</summary>
		static void UnsetNumlockAsyncAscii() noexcept
		{
			const ScanCodeType NumLockState = GetKeyState(static_cast<int>((VK_NUMLOCK)));
			const std::bitset<sizeof(ScanCodeType)* CHAR_BIT> bits(NumLockState);
			if (bits[0])
			{
				auto DoNumlockSend = []()
				{
					auto result = SendVirtualKeyAscii(VK_NUMLOCK, true, true);
					if (result != 1)
						return;
					std::this_thread::sleep_for(std::chrono::milliseconds(15));
					result = SendVirtualKeyAscii(VK_NUMLOCK, true, false);
					if (result != 1)
						return;
				};
				std::thread numLockSender(DoNumlockSend);
				numLockSender.detach(); // fire and forget
			}
		}
		/// <summary>Utility function to map a Virtual Keycode to a scancode, will check the memoization store and update it.</summary>
		/// <param name="vk"> integer virtual keycode</param>
		/// <returns>the scancode</returns>
		[[nodiscard]] static WORD GetScanCode(const int vk) noexcept
		{
			if (vk > std::numeric_limits<VkType>::max() || vk < std::numeric_limits<VkType>::min())
				return 0;
			if (m_scancode_store.contains(vk))
			{
				return static_cast<WORD>(m_scancode_store[vk]);
			}
			const WORD scan = static_cast<WORD> (MapVirtualKeyExA(vk, MAPVK_VK_TO_VSC, nullptr));
			m_scancode_store[vk] = scan;
			return scan;
		}
	};
}