#include "game.hpp"

#include "util/constants.hpp"
#include "states/gamestate.hpp"
#include "states/menustate.hpp"
#include "util/resourcemanager.hpp"

Game::Game()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

	window.setFramerateLimit(FRAMES_PER_SECOND);
	window.setVerticalSyncEnabled(true);

	menuState = new MenuState(this);
	gameState = new GameState(this);

	/* set initial state */
	setCurrentState(STATE_MENU);
}

Game::~Game()
{
	/* delete states */
	delete gameState;
	delete menuState;
}

void Game::processGame()
{
	sf::Clock deltaClock;
	sf::Clock fpsClock;
	sf::Clock halfSecondClock; /* update window title fps every half second */
	float lastTime = 0;

	while (window.isOpen())
	{
		/* time stuff */
		float deltaTime = deltaClock.restart().asSeconds();
		/*if (deltaTime > 0.15f)
			deltaTime = 0.15f;*/

		float currentTime = fpsClock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;
		if (halfSecondClock.getElapsedTime().asMilliseconds() > 500)
		{
			window.setTitle(WINDOW_TITLE + " " + std::to_string(fps) + " FPS");
			halfSecondClock.restart();
		}

		/* process stuff */
		mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		processWindowEvents();

		currentState->processState(deltaTime);

		window.display();
	}
}

void Game::processWindowEvents()
{
	window.clear();
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			exit(0);
			break;
		case sf::Event::GainedFocus:
			windowHasFocus = true;
			break;
		case sf::Event::LostFocus:
			windowHasFocus = false;
			break;
		default:
			currentState->processWindowEvent(event);
		}
	}
}

void Game::setCurrentState(const int &stateId)
{
	switch (stateId)
	{
	case STATE_MENU:
		currentState = menuState;
		break;
	case STATE_GAME:
		gameState->loadCurrentLevel();
		currentState = gameState;
		break;
	default:
		std::cerr << "unknown stateid: " << stateId << std::endl;
	}
}

ResourceManager &Game::getResourceManager()
{
	return resourceManager;
}

sf::RenderWindow &Game::getRenderWindow()
{
	return window;
}

MenuState *Game::getMenuState()
{
	return menuState;
}

GameState *Game::getGameState()
{
	return gameState;
}

State *Game::getCurrentState()
{
	return dynamic_cast<State *>(currentState);
}

sf::Vector2f Game::getMousePosition()
{
	return mousePosition;
}

bool Game::isWindowHasFocus()
{
	return windowHasFocus;
}