#pragma once


#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class Button;
class Game;
class GameState;
class ResourceManager;
class State
{
public:
	State(Game *game);
	virtual ~State();
	void processState(float dt);
	virtual void onButtonPressed(Button *button);

	virtual void processWindowEvent(sf::Event &event);

	Game *getGame();

protected:
	virtual void update(float dt);
	virtual void draw();

protected:
	Game *game;
};
