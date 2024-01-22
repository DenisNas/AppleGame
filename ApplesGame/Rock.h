#pragma once
#include "Constants.h"
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace AppleGame
{
	struct Rock
	{
		Position2D rocksPositions;
		sf::Sprite sprite;
	};

	struct Game;

	void InitRock(Rock& rock, const Game& game);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}
