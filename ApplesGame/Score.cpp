#include "Score.h"
#include "Game.h"

namespace AppleGame
{
	void InitScoreTable(Game& game)
	{

		for (sf::Text& text : game.resultScoreText)
		{

			text.setFont(game.font);
			text.setCharacterSize(20);
			text.setFillColor(sf::Color::Black);
		}

		for (int i = 0; i < NUM_SCORE; ++i)
		{
			game.resultScoreText[i].setString("Player" + std::to_string(i + 1) + ": " + std::to_string(GetRandomNumber(0, 1000)));
			sf::FloatRect controlRect = game.resultScoreText[i].getLocalBounds();
			game.resultScoreText[i].setOrigin(controlRect.width * 0.5f, controlRect.height * 0.5f);
			game.resultScoreText[i].setPosition(SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2.f) + i * 30.f);
			
		}
		
	}
	
	void SaveResultPlayerScore(Game& game)
	{
		game.resultScoreText[0].setString("Player: " + std::to_string(game.numEatenApples));
	}

	void DrawScoreTable(const Game& game, sf::RenderWindow& window)
	{
		for (const sf::Text text : game.resultScoreText)
		{
			window.draw(text);
		}
	}
}

