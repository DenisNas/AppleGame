﻿
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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				break;
			}
		}

		if (game.isStarted)
		{
			UpdateGame(game, deltaTime);

			// Draw game
			window.clear();
			DrawGame(game, window);
		}
		else
		{
			window.clear();

			SetGameOptions(game);

			DrawMenu(game, window);
		}

		window.display();
	}

	// Deinitialization
	DeinializeGame(game);

	return 0;
}
