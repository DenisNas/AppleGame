#pragma once
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	struct Apple
	{
		Position2D applesPositions;
		sf::Sprite sprite;
		bool isEaten;
	};

	struct Game;

	void initApple(Apple& apple, const Game& game);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
