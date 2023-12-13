#include "Game.h"
#include <cassert>

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

		srand((unsigned int)time(NULL));

		const int start = 10;
		const int end = 30;

		game.applesCount = rand() % (end - start + 1) + start;

		game.apples = new Apple[game.applesCount];

		// Init apples
		for (int i = 0; i < game.applesCount; ++i)
		{
			InitApple(game.apples[i], game);
		}

		// Init rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			InitRock(game.rocks[i], game);
		}

		InitMenuText(game);

		InitGameText(game);

		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		// Init player sounds
		game.eatAppleSound.setBuffer(game.eatAppleBuffer);
		game.deathSound.setBuffer(game.deathSoundBuffer);

		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0;

	}

	void UpdateGame(Game& game, float deltaTime)
	{

		Player& player = game.player;

		// Update game state
		if (!game.isGameFinished)
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
		else
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

	void DrawMenu(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background);

		DrawMenuText(game, window);

	}

	void InitGameText(Game& game)
	{
		// Init score text
		game.scoreText.setFont(game.font);
		game.scoreText.setCharacterSize(20);

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

		game.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
	}

	void InitMenuText(Game& game)
	{
		for (sf::Text text: game.menuText)
		{
			text.setFont(game.font);
			text.setCharacterSize(20);
		}

		for (int i = 0; i < 3; ++i)
		{
			sf::FloatRect controlRect = game.controlText.getLocalBounds();
			game.menuText[i].setOrigin(controlRect.width * 0.5f, controlRect.height * 0.5f);
			game.menuText[i].setPosition(SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2 - 30) + i * 30.f);
		}

		game.menuText[2].setString("Press Enter to start");
	}

	void DrawGameText(Game& game, sf::RenderWindow& window)
	{
		game.scoreText.setString("Eaten apples: " + std::to_string(game.numEatenApples));
		window.draw(game.scoreText);

		window.draw(game.controlText);

		if (game.isGameFinished)
		{
			window.draw(game.gameOverText);
		}
	}

	void DrawMenuText(Game& game, sf::RenderWindow& window)
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

		game.menuText[0].setString("Acceleration Press \"1\": " + acceleration);
		game.menuText[1].setString("Endless apples Press \"2\": " + endlessAppales);

		for (const sf::Text text : game.menuText)
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
		for (Rock rock: game.rocks)
		{
			rock.rocksPositions = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		// Reset game state
		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0.f;
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
				game.isGameFinished = true;
				game.timeSinceGameFinish = 0.f;
			}
		}

		// Check screen borders collision
		if (player.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || player.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			player.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || player.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			game.isGameFinished = true;
			game.timeSinceGameFinish = 0.f;
		}

		if (game.isGameFinished) {
			game.deathSound.play();
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
			game.isStarted = true;
		}
	}

	void DeinializeGame(Game& game)
	{
		delete[] game.apples;
	}
}
