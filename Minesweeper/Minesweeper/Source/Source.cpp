#include <time.h>
#include <iostream>
#include "Game/Grid.h"
#include "Menu/MainMenu.h"
#include <Windows.h>
struct MouseInputVars
{
	bool LeftButtonLastFrame = false;
	bool RightButtonLastFrame = false;
	float timePressed = 0.0f;
	float timePassedSinceLastActivation = 0.0f;
};

bool MouseEvents(Grid & grid, const sf::Vector2i &mp, MouseInputVars & miv);
MainMenu::ButtonPressed MouseEvents(MainMenu & menu, const sf::Vector2i &mp, MouseInputVars & miv);

int main()
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);
	// Init Rand	
	srand(static_cast<unsigned>(time(0)));

	

	//Remove when release
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Init program
	Button::Init();
	auto message = TextureManager::Init();
	if (!message)
	{
		std::cout << message.message << std::endl;
	}

	// Create window
	sf::String Title = "MineSweeper, B-Edition";
	sf::RenderWindow window(sf::VideoMode(600, 800), Title, sf::Style::Titlebar | sf::Style::Close);
	window.setIcon(32, 32, TextureManager::g_Bomb.copyToImage().getPixelsPtr());
	
	// Create Menu
	MainMenu menu;
	bool game = false;

	// Create Game
	Grid theGrid;

	Button gameMessage;
	gameMessage.setPosition(0, 32);
	gameMessage.setBackgroundColor(255, 255, 255, 128);
	gameMessage.setOutlineColor(0, 0, 0);
	gameMessage.setTextColor(55, 0, 0);
	MouseInputVars miv;
	bool keyPressed = false;

	sf::Clock loopClock;

	while (window.isOpen())
	{
		float dt = loopClock.restart().asSeconds();
		if (miv.LeftButtonLastFrame)
		{
			miv.timePressed += dt;
			if (miv.timePressed > 0.5f)
				miv.timePassedSinceLastActivation += dt;
		}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (window.hasFocus())
		{
			auto mp = sf::Mouse::getPosition(window);

			if (game)
			{
				theGrid.Update(mp, dt);
				game = MouseEvents(theGrid, mp, miv);

				if (theGrid.isWon())
					gameMessage.setTextString("YOU WON!");
				else if (theGrid.isLost())
					gameMessage.setTextString("YOU DIED!");

				if (!game)
				{
					sf::Vector2u newWinSize;
					newWinSize.x = 600;
					newWinSize.y = 800;
					sf::VideoMode vm = sf::VideoMode(newWinSize.x, newWinSize.y);
					window.close();
					window.create(vm, Title, sf::Style::Titlebar | sf::Style::Close);
					window.setIcon(32, 32, TextureManager::g_Bomb.copyToImage().getPixelsPtr());
				}

			}
			else
			{
				switch (MouseEvents(menu, mp, miv))
				{
				case MainMenu::ButtonPressed::Quit:
					window.close();
					break;
				case MainMenu::ButtonPressed::Play:
					game = true;
					Options::Settings settings =  menu.getSettings();
					theGrid.Init(settings.gridX, settings.gridY, settings.nrOfBombs);
					sf::Vector2u newWinSize;
					newWinSize.x = settings.gridX * 32;
					newWinSize.y = settings.gridY * 32 + 32;
					
					gameMessage.setButtonSize(newWinSize.x, newWinSize.y);
					gameMessage.setTextSize(newWinSize.x / 8);

					sf::VideoMode vm = sf::VideoMode(newWinSize.x, newWinSize.y);
					window.close();
					window.create(vm, Title, sf::Style::Titlebar | sf::Style::Close);
					window.setIcon(32, 32, TextureManager::g_Bomb.copyToImage().getPixelsPtr());
				}
			}
		}



		window.clear();

		if (!game)
			window.draw(menu);
		else
		{
			window.draw(theGrid);

			if (theGrid.isWon() || theGrid.isLost())
				window.draw(gameMessage);
		}



		window.display();
	}

	return 0;
}

bool MouseEvents(Grid & grid, const sf::Vector2i &mp, MouseInputVars & miv)
{
	bool canContinue = true;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!miv.LeftButtonLastFrame)
		{
			canContinue = grid.LeftClick(mp);
			miv.LeftButtonLastFrame = true;
		}
	}
	else
	{
		miv.LeftButtonLastFrame = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!miv.RightButtonLastFrame)
		{
			grid.RightClick(mp);
			miv.RightButtonLastFrame = true;
		}
	}
	else
	{
		miv.RightButtonLastFrame = false;
	}
	return canContinue;
}

MainMenu::ButtonPressed MouseEvents(MainMenu & menu, const sf::Vector2i & mp, MouseInputVars & miv)
{
	MainMenu::ButtonPressed state = MainMenu::ButtonPressed::None;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!miv.LeftButtonLastFrame)
		{
			state = menu.MousePress(mp);
			miv.LeftButtonLastFrame = true;
		}
		else if (menu.isInsideOptions() && 
			miv.timePressed > 0.5f &&
			miv.timePassedSinceLastActivation > 0.1f)
		{
			state = menu.MousePress(mp);
			miv.timePassedSinceLastActivation = 0.0f;
		}
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		miv.timePressed = 0.0f;
		miv.timePassedSinceLastActivation = 0.0f;
		miv.LeftButtonLastFrame = false;
	}
	return state;
}
