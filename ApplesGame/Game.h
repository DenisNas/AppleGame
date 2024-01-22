#pragma once

#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Constants.h"
#include "Score.h"

//test comment

namespace AppleGame
{
	struct Game
	{
		Player player;

		// Apples data
		Apple *apples;

		// Rocks data
		Rock rocks[NUM_ROCKS];

		// Score table data
		Score scoreTable[NUM_SCORE];

		// Game mode selection 
		// 0 bit = on\off acceleration
		// 1 bit = on\off endless apples
		int settings = 8;
		// Global game data
		int applesCount;
		int numEatenApples = 0;
		bool isGameFinished = false;
		bool isStarted = false;
		bool accelerationChanged = false;
		bool endlessApplesChange = false;
		float timeSinceGameFinish = 0.f;
		sf::RectangleShape background;

		// Objects textures
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;

		// Sounds
		sf::SoundBuffer eatAppleBuffer;
		sf::SoundBuffer deathSoundBuffer;

		sf::Sound deathSound;
		sf::Sound eatAppleSound;

		// Text
		sf::Font font;
		sf::Text appleScoreText;
		sf::Text controlText;
		sf::Text gameOverText;

		sf::Text menuText[3];
		sf::Text resultScoreText[NUM_SCORE];

	};

	void InitGame(Game& game);
	
	void InitGameText(Game& game);

	void InitMenuText(Game& game);
	
	void UpdateGame(Game& game, float deltaTime);

	void UpdateEatenAppes(Game& game);

	void CheckCollisionsWithRockOrBorder(Game& game);

	void SetGameOptions(Game& game);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void DrawMenu(Game& game, sf::RenderWindow& window);

	void DrawGameText(Game& game, sf::RenderWindow& window);

	void DrawMenuText(Game& game, sf::RenderWindow& window);

	void ResetGame(Game& game);

	void DeinializeGame(Game& game);

}
