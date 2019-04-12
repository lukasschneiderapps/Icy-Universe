#pragma once

#include "util/resourcemanager.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class State;
class MenuState;
class GameState;
class Game
{
public:
	Game();
	~Game();

	void processGame();
	void processWindowEvents();
	void setCurrentState(const int &stateId);

	ResourceManager &getResourceManager();
	sf::RenderWindow &getRenderWindow();

	MenuState *getMenuState();
	GameState *getGameState();

	State *getCurrentState();

	sf::Vector2f getMousePosition();

	bool isWindowHasFocus();

private:
	sf::RenderWindow window;

	State *currentState;
	MenuState *menuState;
	GameState *gameState;

	ResourceManager resourceManager;

	sf::Vector2f mousePosition;

	bool windowHasFocus;
};