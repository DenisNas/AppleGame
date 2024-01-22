#include "Rock.h"
#include "Game.h"

namespace AppleGame
{
	void InitRock(Rock& rock, const Game& game)
	{
		rock.rocksPositions = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		rock.sprite.setTexture(game.rockTexture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteOrigin(rock.sprite, 0.5f, 0.5f);
	}
	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition(rock.rocksPositions.x, rock.rocksPositions.y);
		window.draw(rock.sprite);
	}
}
