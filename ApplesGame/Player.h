#pragma once
#include "Math.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		// Player data
		Position2D playerPosition;
		float playerSpeed = INITIAL_SPEED;
		PlayerDirection playerDirection = PlayerDirection::Right;
		sf::Sprite sprite;
	};

	struct Game;

	void InitPlayer(Player& player, const Game& game);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
	void TurnAround(Player& player);
	void ChangeDirection(Player& player);
	void MovePlayer(Player& player, float deltaTime);
}