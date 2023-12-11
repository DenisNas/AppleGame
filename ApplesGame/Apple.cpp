#include "Apple.h"
#include "Game.h"


namespace AppleGame
{
	void initApple(Apple& apple, const Game& game)
	{
		apple.applesPositions = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteOrigin(apple.sprite, 0.5f, 0.5f);

		apple.isEaten = false;
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (!apple.isEaten)
		{
			apple.sprite.setPosition(apple.applesPositions.x, apple.applesPositions.y);
			window.draw(apple.sprite);
		}
	}
}
