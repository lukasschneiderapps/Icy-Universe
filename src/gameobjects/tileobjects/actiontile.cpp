#include "actiontile.hpp"

#include "../../util/constants.hpp"
#include "../../states/gamestate.hpp"
#include "../../game.hpp"

/* no collision, something happens when colliding (or not)
finish, start, speedup (can go to left, right, up or down) */

ActionTile::ActionTile(Game *game, int tileId, float x, float y) :
	Tile(game, tileId, x, y, false, false, false, false) {}

void ActionTile::onCollision(Tile &other)
{
	if (other.getTileId() == TILE_PLAYER)
	{
		switch (tileId)
		{
			/* finish */
		case TILE_FINISH:
			game->getGameState()->finish();
			break;
			/* speed ups */
		case TILE_SPEED_UP_LEFT:
		{
			sf::Vector2f movingVector = game->getGameState()->getPlayer().getMovingVector();
			movingVector.x = -PLAYER_SPEED_UP_SPEED_X;
			game->getGameState()->getPlayer().setMovingVector(movingVector);

			/*if (game->getResourceManager().getSound("speed_up")->getStatus() != sf::Sound::Status::Playing)
			{
				game->getResourceManager().getSound("speed_up")->play();
			}*/
		}
		break;
		case TILE_SPEED_UP_RIGHT:
		{
			sf::Vector2f movingVector = game->getGameState()->getPlayer().getMovingVector();
			movingVector.x = PLAYER_SPEED_UP_SPEED_X;
			game->getGameState()->getPlayer().setMovingVector(movingVector);

			/*if (game->getResourceManager().getSound("speed_up")->getStatus() != sf::Sound::Status::Playing)
			{
				game->getResourceManager().getSound("speed_up")->play();
			}*/
		}
		break;
		case TILE_SPEED_UP_UP:
		{
			sf::Vector2f movingVector = game->getGameState()->getPlayer().getMovingVector();
			movingVector.y = -PLAYER_SPEED_UP_SPEED_Y;
			game->getGameState()->getPlayer().setMovingVector(movingVector);

			/*if (game->getResourceManager().getSound("speed_up")->getStatus() != sf::Sound::Status::Playing)
			{
				game->getResourceManager().getSound("speed_up")->play();
			}*/
		}
		break;
		case TILE_SPEED_UP_DOWN:
		{
			sf::Vector2f movingVector = game->getGameState()->getPlayer().getMovingVector();
			movingVector.y = PLAYER_SPEED_UP_SPEED_Y;
			game->getGameState()->getPlayer().setMovingVector(movingVector);

			/*if (game->getResourceManager().getSound("speed_up")->getStatus() != sf::Sound::Status::Playing)
			{
				game->getResourceManager().getSound("speed_up")->play();
			}*/
		}
		break;
		}
	}
}
