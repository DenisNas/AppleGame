#pragma once
#include "string"
#include <SFML/Graphics.hpp>

namespace AppleGame

{

	struct Game;

	struct Score
	{
		std::string playerName;
		int score;
	};

	void InitScoreTable(Game& game);
	void SaveResultPlayerScore(Game& game);
	void DrawScoreTable(const Game& game, sf::RenderWindow& window);
}