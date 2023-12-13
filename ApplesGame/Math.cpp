#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		const float dx = (float)fabs(rect1Position.x - rect2Position.x);
		const float dy = (float)fabs(rect1Position.y - rect2Position.y);
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	bool IsCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
	{
		const float squareDistance = (circle1Position.x - circle2Position.x) *
			(circle1Position.x - circle2Position.x) +
			(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		const float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
		return squareDistance <= squareRadiusSum;
	}
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		const sf::FloatRect spriteRect = sprite.getLocalBounds();
		const sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
	void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		const sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(spriteRect.width * originX, spriteRect.height * originY);

	}
}	 
