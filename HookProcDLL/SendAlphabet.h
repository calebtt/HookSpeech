#pragma once
#include "stdafx.h"
#include "SendKeyInput.h"
namespace sds
{
	class SendAlphabet
	{
		using Sender = sds::Utilities::SendKeyInput;
		std::string m_workingAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::wstring m_translationAlphabet = L"àƀćďĕƒğħíĵĸlmnǒpqrƨţuvwxÿzĀßCĐEFĢĦIJƘŁMNOƤQRƧŦUVWXYZ";
	public:
		SendAlphabet() = default;
		//Simulates a hardware key-press for characters.
		static void Send(int vk, bool down) noexcept
		{
			Sender::SendVirtualKeyUnicode(vk, down);
		}
		//Determines if "int vk" is in the working alphabet, this is the english alphabet a-z and A-Z.
		//Returns: true if character is in working alphabet, false otherwise.
		[[nodiscard]] wchar_t IsTranslatable(const int vk) const noexcept
		{
			const SHORT ShiftState = GetKeyState(static_cast<int>((VK_SHIFT))); // shift key
			const SHORT CapsLockState = GetKeyState(VK_CAPITAL); // caps lock key
			constexpr int shiftBitLength = sizeof(SHORT) * 8;
			constexpr std::size_t shiftBitLastIndex = shiftBitLength - 1;
			constexpr int capsBitLength = sizeof(SHORT) * 8;
			const std::bitset<shiftBitLength> shiftBits(ShiftState);
			const std::bitset<capsBitLength> capsLockBits(CapsLockState);
			const bool isShiftDown = shiftBits[shiftBitLastIndex];
			const bool isCapsDown = capsLockBits[0];
			auto capsAware = static_cast<unsigned char>(vk);
			const bool isLowerPossible = std::isalnum(capsAware);
			if (isLowerPossible && ((isShiftDown && isCapsDown) || (!isCapsDown && !isShiftDown)))
				capsAware = static_cast<unsigned char>(std::tolower(vk));
			const std::size_t ind = m_workingAlphabet.find(static_cast<char>(capsAware));
			if(ind != decltype(m_workingAlphabet)::npos)
			{
				return m_translationAlphabet[ind];
			}
			return 0;
		}
		//Updates the alphabet the English characters are translated to.
		//Note: The new alphabet "wstring update" needs to be the same length as the internal m_workingAlphabet.
		//Returns: false on update failure, true on success.
		bool UpdateTranslationAlphabet(const std::wstring update) noexcept
		{
			if (m_translationAlphabet.size() != update.size())
				return false;
			m_translationAlphabet = update;
			return true;

		}
		bool UpdateWorkingAlphabet(const std::string update) noexcept
		{
			if (m_workingAlphabet.size() != update.size())
				return false;
			m_workingAlphabet = update;
			return true;

		}
		std::size_t GetWorkingAlphabetSize() const noexcept
		{
			return m_workingAlphabet.size();
		}
		std::string GetWorkingAlphabet() const noexcept
		{
			return m_workingAlphabet;
		}
		std::wstring GetTranslationAlphabet() const noexcept
		{
			return m_translationAlphabet;
		}
		std::size_t GetTranslationAlphabetSize() const noexcept
		{
			return m_translationAlphabet.size();
		}
	};
}