#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class TextureManager
{
public:
	struct InitMessage
	{
		std::string message = "";
		bool status = true;
		explicit operator bool() const
		{
			return status;
		}
	};

public:
	static InitMessage Init();

	static sf::Texture g_Reset;
	static sf::Texture g_Empty;
	static sf::Texture g_Undiscovered;
	static sf::Texture g_Bomb;
	static sf::Texture g_BombPressed;
	static sf::Texture g_Flag;
	static sf::Texture g_FlagFail;
	static sf::Texture g_Number[8];
};