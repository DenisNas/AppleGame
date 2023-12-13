#include "Player.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

namespace AppleGame
{
	void InitPlayer(Player& player, const Game& game)
	{
		// Init player state
		player.playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;

		//Init player sprite
		player.sprite.setTexture(game.playerTexture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteOrigin(player.sprite, 0.5f, 0.5f);

	}
	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
		window.draw(player.sprite);
	}
	void TurnAround(Player& player)
	{

		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		player.sprite.setRotation(0.f);

		switch (player.playerDirection)
		{
		case PlayerDirection::Up:
		{
			player.sprite.setRotation(260.f);
		}
		case PlayerDirection::Right:
		{
			break;
		}
		case PlayerDirection::Down:
		{
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left:
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
			break;
		}
		}
	}
	void ChangeDirection(Player& player)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.playerDirection = PlayerDirection::Down;
		}

		TurnAround(player);
	}
	void MovePlayer(Player& player, float deltaTime)
	{
		switch (player.playerDirection)
		{
		case PlayerDirection::Right:
		{
			player.playerPosition.x += player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			player.playerPosition.y -= player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			player.playerPosition.x -= player.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			player.playerPosition.y += player.playerSpeed * deltaTime;
			break;
		}
		}
	}
}
