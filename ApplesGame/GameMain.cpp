
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"


int main()
{
	using namespace AppleGame;

	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// Game initialization
	Game game;
	InitGame(game);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{

		sf::sleep(sf::milliseconds(16));

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (game.gameStateStack.back() != GameState::StartMenu && game.gameStateStack.back() != GameState::Finished) {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					if (game.gameStateStack.back() != GameState::GMenu)
					{
						PushGameState(game, GameState::GMenu);
					}
					else if (game.gameMenu.gameMenuStateStack.back() != MenuLine::Main)
					{
						game.gameMenu.gameMenuStateStack.pop_back();
					}
					else {
						PopGameState(game);
					}
				}
				if (game.gameStateStack.back() == GameState::GMenu) {
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
					{
						OpenMenuOption(game.gameMenu);
					}
					else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
					{
						MovePointerDown(game.gameMenu);
					}
					else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
					{
						MovePointerUp(game.gameMenu);
					}

					if (game.gameMenu.gameMenuStateStack.back() == MenuLine::Escape)
					{
						if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
						{
							game.gameMenu.gameMenuStateStack.pop_back();
						}
						else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y)
						{
							window.close();
							break;
						}
					}
				}
			}
		}

		if (game.gameStateStack.back() == GameState::StartMenu)
		{
			window.clear();

			SetGameOptions(game);

			DrawStartMenu(game, window);
		}
		else if(game.gameStateStack.back() == GameState::GMenu)
		{
			window.clear();

			if (game.gameMenu.gameMenuStateStack.back() == MenuLine::Escape)
			{
				DrawEscapeText(game, window);
			}
			else if (game.gameMenu.gameMenuStateStack.back() == MenuLine::Score)
			{
				SaveResultPlayerScore(game);
				DrawScoreTable(game, window);
			}
			else {
				DrawGameMenuText(game, window);
			}
		}
		else
		{
			UpdateGame(game, deltaTime);

			// Draw game
			window.clear();
			DrawGame(game, window);
		}

		window.display();
	}

	// Deinitialization
	DeinializeGame(game);

	return 0;
}
