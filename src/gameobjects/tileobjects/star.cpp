#include "star.hpp"

#include "../../util/constants.hpp"
#include "../../util/resourcemanager.hpp"
#include "../../states/gamestate.hpp"
#include "../../game.hpp"

Star::Star(Game *game, float x, float y) :
	Tile(game, TILE_STAR, x, y, false, false, false, false),
	collected(false) {}

void Star::reset()
{
	if (collected)
	{
		collected = false;
		game->getGameState()->changeStarsCollected(-1);
	}
}

void Star::onCollision(Tile &other)
{
	if (other.getTileId() == TILE_PLAYER && (!collected))
	{
		collected = true;

		game->getGameState()->changeStarsCollected(+1);
		//game->getResourceManager().getSound("on_collision_star")->play();
	}
}

void Star::draw()
{
	/* draw if not collected */
	if (!collected)
	{
		/*CustomSprite::draw();*/
		renderWindow->draw(sprite);
	}
}

bool Star::isCollected()
{
	return collected;
}

void Star::setCollected(bool collected)
{
	this->collected = collected;
}
