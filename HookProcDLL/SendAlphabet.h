#pragma once
#include "stdafx.h"
#include "SendKeyInput.h"
#include <fstream>
namespace sds
{
	class SendAlphabet
	{
		sds::Utilities::SendKeyInput m_sender;
		std::string m_workingAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::wstring m_translationAlphabet = L"àƀćďĕƒğħíĵĸlmnǒpqrƨţuvwxÿzĀßCĐEFĢĦIJƘŁMNOƤQRƧŦUVWXYZ";
	public:
		SendAlphabet() = default;
		//Simulates a hardware key-press for characters.
		void Send(int vk, bool down)
		{
			m_sender.SendUnicode(vk, down);
		}
		//Determines if "int vk" is in the working alphabet, this is the english alphabet a-z and A-Z.
		//Returns: true if character is in working alphabet, false otherwise.
		[[nodiscard]] wchar_t IsTranslatable(const int vk) const noexcept
		{
			const SHORT ShiftState = GetKeyState(static_cast<int>((VK_SHIFT))); // shift key
			const SHORT CapsLockState = GetKeyState(VK_CAPITAL); // caps lock key
			constexpr int shiftBitLength = sizeof(SHORT) * 8;
			constexpr int capsBitLength = sizeof(SHORT) * 8;
			const std::bitset<shiftBitLength> shiftBits(ShiftState);
			const std::bitset<capsBitLength> capsLockBits(CapsLockState);
			const bool isShiftDown = shiftBits[shiftBitLength-1];
			const bool isCapsDown = capsLockBits[0];
			int capsAware = vk;
			if (isShiftDown && isCapsDown)
				capsAware = std::tolower(vk);
			else if(!isCapsDown && !isShiftDown)
				capsAware = std::tolower(vk);
			const size_t ind = m_workingAlphabet.find(static_cast<char>(capsAware));
			if(ind != std::string::npos)
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
		size_t GetWorkingAlphabetSize() const noexcept
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
		size_t GetTranslationAlphabetSize() const noexcept
		{
			return m_translationAlphabet.size();
		}
	};
}