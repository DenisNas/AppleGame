#pragma once

#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Constants.h"
#include "Score.h"
#include "GameMenu.h"

//test comment

namespace AppleGame
{

	enum GameState
	{
		None = 0,
		StartMenu,
		ScoreTable,
		Playing,
		Finished,
		GMenu,
		Exit
	};

	struct Game
	{
		Player player;

		// Apples data
		std::vector<Apple> apples;

		// Rocks data
		std::vector<Rock> rocks;

		//game menu
		GameMenu gameMenu;

		// Game mode selection 
		// 0 bit = on\off acceleration
		// 1 bit = on\off endless apples
		int settings = 8;
		// Global game data
		int applesCount;
		int numEatenApples = 0;

		std::vector<GameState> gameStateStack;

		/*bool isGameFinished = false;
		bool isStarted = false;*/
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
		sf::Text EscapeText;

		std::vector<sf::Text> startMenuText;
		
		// Score table data
		std::vector<sf::Text> resultScoreText;

	};

	void InitGame(Game& game);
	
	void InitGameText(Game& game);

	void InitStartMenuText(Game& game);

	
	
	void UpdateGame(Game& game, float deltaTime);

	void UpdateEatenAppes(Game& game);

	void CheckCollisionsWithRockOrBorder(Game& game);

	void SetGameOptions(Game& game);

	void DrawGame(Game& game, sf::RenderWindow& window);

	void DrawStartMenu(Game& game, sf::RenderWindow& window);



	void DrawGameText(Game& game, sf::RenderWindow& window);

	void DrawStartMenuText(Game& game, sf::RenderWindow& window);



	void ResetGame(Game& game);

	void DeinializeGame(Game& game);

	void PushGameState(Game& game, GameState gamestate);
	
	void PopGameState(Game& game);

	void SwitchGameState(Game& game, GameState newState);

}
