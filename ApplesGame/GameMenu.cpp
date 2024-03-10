#include "Game.h"
#include "GameMenu.h"

namespace AppleGame
{
	
	void OpenMenuOption(GameMenu& gameMenu)
	{
		MenuLine line = static_cast<MenuLine>(gameMenu.chousenLine + 1);

		if (line == MenuLine::Score)
		{
			gameMenu.gameMenuStateStack.push_back(MenuLine::Score);
		}
		else if (line == MenuLine::Escape){
			gameMenu.gameMenuStateStack.push_back(MenuLine::Escape);
		}
	};

	void GoBackInMenu(GameMenu& gameMenu) {
		gameMenu.gameMenuStateStack.pop_back();
	}

	void MovePointerUp(GameMenu& gameMenu)
	{
		if (gameMenu.chousenLine > 0)
		{
			gameMenu.chousenLine--;
		}
	};

	void MovePointerDown(GameMenu& gameMenu)
	{
		if (gameMenu.chousenLine < gameMenu.gameMenuText.size() - 1)
		{
			gameMenu.chousenLine++;
		}
	};

	void InitGameMenu(Game& game)
	{
		game.gameMenu.gameMenuStateStack.push_back(MenuLine::Main);
		InitGameMenuText(game);
	};

	void InitGameMenuText(Game& game)
	{
		
		game.gameMenu.gameMenuText.reserve(2);

		for (int i = 0; i < 2; ++i)
		{
			game.gameMenu.gameMenuText.push_back(sf::Text{});

			game.gameMenu.gameMenuText[i].setFont(game.font);
			game.gameMenu.gameMenuText[i].setCharacterSize(20);

			sf::FloatRect controlRect = game.controlText.getLocalBounds();
			game.gameMenu.gameMenuText[i].setOrigin(controlRect.width * 0.5f, controlRect.height * 0.5f);
			game.gameMenu.gameMenuText[i].setPosition(SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2 - 30) + i * 30.f);
		}

		game.gameMenu.gameMenuText[0].setString("Score table");
		game.gameMenu.gameMenuText[1].setString("Exit");
	}

	void DrawGameMenuText(Game& game, sf::RenderWindow& window)
	{
		int chosenLine = game.gameMenu.chousenLine;

		for (int i = 0; i < 2; ++i)
		{
			
			if ( i != chosenLine && game.gameMenu.gameMenuText[chosenLine].getFillColor() != sf::Color::White)
			{
				game.gameMenu.gameMenuText[i].setFillColor(sf::Color::White);
			}
		}

		if (game.gameMenu.gameMenuText[chosenLine].getFillColor() != sf::Color::Red)
		{
			game.gameMenu.gameMenuText[chosenLine].setFillColor(sf::Color::Red);
		}

		for (const sf::Text text : game.gameMenu.gameMenuText)
		{
			window.draw(text);
		}


	}

	void DrawEscapeText(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.EscapeText);
	};

}