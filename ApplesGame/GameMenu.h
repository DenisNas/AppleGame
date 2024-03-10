#pragma once
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	enum MenuLine{
		Main,
		Score,
		Escape
	};

	struct Game;

	struct GameMenu
	{
		int chousenLine = 0;

		std::vector<sf::Text> gameMenuText;

		std::vector<MenuLine> gameMenuStateStack;
	};

	void OpenMenuOption(GameMenu& gameMenu);
	void GoBackInMenu(GameMenu& gameMenu);
	void MovePointerDown(GameMenu& gameMenu);
	void MovePointerUp(GameMenu& gameMenu);

	void InitGameMenu(Game& game);
	void InitGameMenuText(Game& game);
	void DrawGameMenu(Game& game, sf::RenderWindow& window);
	void DrawGameMenuText(Game& game, sf::RenderWindow& window);
	void DrawEscapeText(Game& game, sf::RenderWindow& window);

}