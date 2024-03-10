#include "Game.h"
#include <cassert>
#include "GameMenu.h"

namespace AppleGame
{
	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

		assert(game.eatAppleBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(game.deathSoundBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\WaybulooArial-Bold.ttf"));

		InitPlayer(game.player, game);

		const int start = 10;
		const int end = 30;

		srand((unsigned int)time(NULL));

		game.applesCount = GetRandomNumber(start, end);

		game.apples.reserve(game.applesCount);

		// Init apples
		for (int i = 0; i < game.applesCount; ++i)
		{
			game.apples.push_back(Apple{});
			InitApple(game.apples[i], game);
		}

		game.rocks.reserve(NUM_ROCKS);

		// Init rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			game.rocks.push_back(Rock{});
			InitRock(game.rocks[i], game);
		}

		InitGameText(game);

		InitStartMenuText(game);

		InitScoreTable(game);

		InitGameMenu(game);

		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		// Init player sounds
		game.eatAppleSound.setBuffer(game.eatAppleBuffer);
		game.deathSound.setBuffer(game.deathSoundBuffer);

		game.numEatenApples = 0;
		//game.isGameFinished = false;
		game.timeSinceGameFinish = 0;
		
		PushGameState(game, GameState::StartMenu);
	}

	void UpdateGame(Game& game, float deltaTime)
	{

		Player& player = game.player;

		// Update game state
		if (game.gameStateStack.back() == GameState::Playing)
		{
			// Handle input
			ChangeDirection(player);

			// Calculate Position
			MovePlayer(player, deltaTime);

			// Find player collisions with apples
			UpdateEatenAppes(game);

			// Find player collisions with rocks
			CheckCollisionsWithRockOrBorder(game);
		}
		else if(game.gameStateStack.back() == GameState::Finished)
		{
			if (game.timeSinceGameFinish <= PAUSE_LENGTH)
			{
				game.timeSinceGameFinish += deltaTime;
				game.background.setFillColor(sf::Color::Red);
			}
			else
			{
				ResetGame(game);
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{

		window.draw(game.background);

		DrawPlayer(game.player, window);

		for (int i = 0; i < game.applesCount; ++i)
		{
			DrawApple(game.apples[i], window);
		}

		for (Rock rock: game.rocks)
		{
			DrawRock(rock, window);
		}

		DrawGameText(game, window);

	}

	void DrawStartMenu(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background);

		DrawStartMenuText(game, window);

	}

	void InitGameText(Game& game)
	{
		// Init score text
		game.appleScoreText.setFont(game.font);
		game.appleScoreText.setCharacterSize(20);

		// Init controll text
		game.controlText.setFont(game.font);
		game.controlText.setCharacterSize(20);
		game.controlText.setString(L"left: ← rigth: → down: ↓ up: ↑");

		sf::FloatRect controlRect = game.controlText.getLocalBounds();
		game.controlText.setOrigin(controlRect.width * 0.5f, controlRect.height * 0.5f);
		game.controlText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 30.f);

		// Init game over text
		game.gameOverText.setString("GAME OVER");
		game.gameOverText.setFont(game.font);
		game.gameOverText.setCharacterSize(40);
		game.gameOverText.setFillColor(sf::Color::Black);

		sf::FloatRect gameOverRect = game.gameOverText.getLocalBounds();
		game.gameOverText.setOrigin(gameOverRect.width * 0.5f, gameOverRect.height * 0.5f);

		game.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 50);

		game.EscapeText.setString("Are you sure? Type y/n");
		game.EscapeText.setFont(game.font);
		game.EscapeText.setCharacterSize(40);
		game.EscapeText.setFillColor(sf::Color::White);

		sf::FloatRect escapeRect = game.EscapeText.getLocalBounds();
		game.EscapeText.setOrigin(escapeRect.width * 0.5f, escapeRect.height * 0.5f);

		game.EscapeText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 50);
	}

	void InitStartMenuText(Game& game)
	{

		game.startMenuText.reserve(3);

		for (int i = 0; i < 3; ++i)
		{
			game.startMenuText.push_back(sf::Text{});

			game.startMenuText[i].setFont(game.font);
			game.startMenuText[i].setCharacterSize(20);

			sf::FloatRect controlRect = game.controlText.getLocalBounds();
			game.startMenuText[i].setOrigin(controlRect.width * 0.5f, controlRect.height * 0.5f);
			game.startMenuText[i].setPosition(SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2 - 30) + i * 30.f);
		}

		game.startMenuText[2].setString("Press Enter to start");
	}

	void DrawGameText(Game& game, sf::RenderWindow& window)
	{
		game.appleScoreText.setString("Eaten apples: " + std::to_string(game.numEatenApples));
		window.draw(game.appleScoreText);

		window.draw(game.controlText);

		if (game.gameStateStack.back() == GameState::Finished)
		{
			window.draw(game.gameOverText);
			DrawScoreTable(game, window);
		}
	}

	void DrawStartMenuText(Game& game, sf::RenderWindow& window)
	{
		std::string acceleration;
		std::string endlessAppales;

		if (game.settings & (1 << 0)) {
			acceleration = "on";
		}
		else {
			acceleration = "off";
		}

		if (game.settings & (1 << 1)) {
			endlessAppales = "on";
		}
		else {
			endlessAppales = "off";
		}

		game.startMenuText[0].setString("Acceleration Press \"1\": " + acceleration);
		game.startMenuText[1].setString("Endless apples Press \"2\": " + endlessAppales);

		for (const sf::Text text : game.startMenuText)
		{
			window.draw(text);
		}
	}

	void ResetGame(Game& game)
	{

		Player& player = game.player;

		// Reset backgound
		game.background.setFillColor(sf::Color::Black);

		// Reset player
		player.playerPosition.x = SCREEN_WIDTH / 2.f;
		player.playerPosition.y = SCREEN_HEIGHT / 2.f;
		player.playerSpeed = INITIAL_SPEED;
		player.playerDirection = PlayerDirection::Right;

		// Reset apples
		for (int i = 0; i < game.applesCount; ++i)
		{
			game.apples[i].applesPositions = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		// Reset rocks
		for (Rock& rock: game.rocks)
		{
			rock.rocksPositions = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		// Reset game state
		game.numEatenApples = 0;
		game.gameStateStack.clear();
		game.timeSinceGameFinish = 0.f;
		PushGameState(game, GameState::Playing);
	}

	void UpdateEatenAppes(Game& game)
	{
		Player& player = game.player;

		for (int i = 0; i < game.applesCount; ++i)
		{
			if (!game.apples[i].isEaten)
			{
				if (IsCirclesCollide(player.playerPosition, PLAYER_SIZE / 2.f,
					game.apples[i].applesPositions, APPLE_SIZE / 2.f))
				{
					game.eatAppleSound.play();
					if (game.settings & (1 << 1))
					{
						game.apples[i].applesPositions = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					}
					else
					{
						game.apples[i].isEaten = true;
					}
					++game.numEatenApples;
					if (game.settings & (1 << 0))
					{
						player.playerSpeed += ACCELERATION;
					}

				}
			}
		}
	}

	void CheckCollisionsWithRockOrBorder(Game& game)
	{
		Player& player = game.player;

		for (const Rock rock : game.rocks)
		{
			if (IsRectanglesCollide(player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE },
				rock.rocksPositions, { ROCK_SIZE, ROCK_SIZE }))
			{
				PushGameState(game, GameState::Finished);
				game.timeSinceGameFinish = 0.f;
			}
		}

		// Check screen borders collision
		if (player.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || player.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			player.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || player.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			PushGameState(game, GameState::Finished);
			game.timeSinceGameFinish = 0.f;
		}

		if (game.gameStateStack.back() == GameState::Finished) {
			game.deathSound.play();
			SaveResultPlayerScore(game);
		}
	}

	void SetGameOptions(Game& game)
	{

		// Set acceleration
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (!game.accelerationChanged)
			{
				game.settings = game.settings ^ 1 << 0;
				game.accelerationChanged = true;
			}
		}
		else
		{
			game.accelerationChanged = false;
		}

		// Set endless apples
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (!game.endlessApplesChange)
			{
				game.settings = game.settings ^ 1 << 1;
				game.endlessApplesChange = true;
			}
		}
		else
		{
			game.endlessApplesChange = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			PushGameState(game, GameState::Playing);
		}
	}

	void DeinializeGame(Game& game)
	{
		
	}
	void PushGameState(Game& game, GameState gamestate)
	{
		game.gameStateStack.push_back(gamestate);
	}
	void PopGameState(Game& game)
	{
		game.gameStateStack.pop_back();
	}
	void SwitchGameState(Game& game, GameState newState)
	{
		std::vector<GameState> stack = game.gameStateStack;
		GameState oldState = stack.back();

		stack.pop_back();
		stack.push_back(newState);
	}
}
