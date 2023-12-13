#pragma once
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	struct Game;

	struct Apple
	{
		Position2D applesPositions;
		sf::Sprite sprite;
		bool isEaten = false;
	};

	void InitApple(Apple& apple, const Game& game);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
