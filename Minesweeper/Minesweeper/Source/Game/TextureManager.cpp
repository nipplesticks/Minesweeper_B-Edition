#include "TextureManager.h"


sf::Texture TextureManager::g_Reset;
sf::Texture TextureManager::g_Empty;
sf::Texture TextureManager::g_Undiscovered;
sf::Texture TextureManager::g_Bomb;
sf::Texture TextureManager::g_BombPressed;
sf::Texture TextureManager::g_Flag;
sf::Texture TextureManager::g_FlagFail;
sf::Texture TextureManager::g_Number[8];


TextureManager::InitMessage TextureManager::Init()
{
	InitMessage im;
	if (!g_Empty.loadFromFile("Assets/Empty.jpg"))
	{
		im.status = false;
		im.message += "Empty.jpg could not load\n";
	}
	if (!g_Reset.loadFromFile("Assets/Reset.jpg"))
	{
		im.status = false;
		im.message += "Empty.jpg could not load\n";
	}
	if (!g_Undiscovered.loadFromFile("Assets/UnDiscovered.jpg"))
	{
		im.status = false;
		im.message += "UnDiscovered.jpg could not load\n";
	}
	if (!g_Bomb.loadFromFile("Assets/Bomb.jpg"))
	{
		im.status = false;
		im.message += "Bomb.jpg could not load\n";
	}
	if (!g_BombPressed.loadFromFile("Assets/BombPressed.jpg"))
	{
		im.status = false;
		im.message += "BombPressed.jpg could not load\n";
	}
	if (!g_Flag.loadFromFile("Assets/Flag.jpg"))
	{
		im.status = false;
		im.message += "Flag.jpg could not load\n";
	}
	if (!g_FlagFail.loadFromFile("Assets/FlagFail.jpg"))
	{
		im.status = false;
		im.message += "FlagFailed.jpg could not load\n";
	}
	if (!g_Number[0].loadFromFile("Assets/One.jpg"))
	{
		im.status = false;
		im.message += "One.jpg could not load\n";
	}
	if (!g_Number[1].loadFromFile("Assets/Two.jpg"))
	{
		im.status = false;
		im.message += "Two.jpg could not load\n";
	}
	if (!g_Number[2].loadFromFile("Assets/Three.jpg"))
	{
		im.status = false;
		im.message += "Three.jpg could not load\n";
	}
	if (!g_Number[3].loadFromFile("Assets/Four.jpg"))
	{
		im.status = false;
		im.message += "Four.jpg could not load\n";
	}
	if (!g_Number[4].loadFromFile("Assets/Five.jpg"))
	{
		im.status = false;
		im.message += "Five.jpg could not load\n";
	}
	if (!g_Number[5].loadFromFile("Assets/Six.jpg"))
	{
		im.status = false;
		im.message += "Six.jpg could not load\n";
	}
	if (!g_Number[6].loadFromFile("Assets/Seven.jpg"))
	{
		im.status = false;
		im.message += "Seven.jpg could not load\n";
	}
	if (!g_Number[7].loadFromFile("Assets/Eight.jpg"))
	{
		im.status = false;
		im.message += "Eight.jpg could not load\n";
	}


	return im;
}
