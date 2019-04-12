#pragma once

static const std::string WINDOW_TITLE = std::string("ICY UNIVERSE 2D");

static const int WINDOW_WIDTH = 960;
static const int WINDOW_HEIGHT = 640;
static const int FRAMES_PER_SECOND = 60;

static const bool DEBUG = true;

static const float TILE_SIZE = 32.0f;
static const float TILES_X = WINDOW_WIDTH / TILE_SIZE;
static const float TILES_Y = WINDOW_HEIGHT / TILE_SIZE;

static const float PLAYER_MOVEMENT_REPEATS = 4.0f;
static const float PLAYER_MOVEMENT_SPEED = 20.0f / PLAYER_MOVEMENT_REPEATS;
static const float PLAYER_MAX_MOVEMENT_SPEED = 200.0f / PLAYER_MOVEMENT_REPEATS;
static const float PLAYER_MOVEMENT_SUBSTRACTION = 100.0f * PLAYER_MAX_MOVEMENT_SPEED / 10.0f / PLAYER_MOVEMENT_REPEATS;
static const float PLAYER_SPEED_UP_SPEED_X = 500.0f / PLAYER_MOVEMENT_REPEATS;
static const float PLAYER_SPEED_UP_SPEED_Y = 1500.0f / PLAYER_MOVEMENT_REPEATS;

static const float PLAYER_FALLING_SPEED = 1333.0f / PLAYER_MOVEMENT_REPEATS;
static const float PLAYER_MAX_FALLING_SPEED = 1000.0f / PLAYER_MOVEMENT_REPEATS;

static const float PLAYER_JUMPING_SPEED = -250.0f;
static const float PLAYER_SPRING_JUMPING_SPEED = -330.0f;
static const float PLAYER_MAX_JUMPING_SPEED = PLAYER_SPRING_JUMPING_SPEED;
static const float PLAYER_GRAVITY = -(10.0f * PLAYER_MAX_JUMPING_SPEED / 200.0f / PLAYER_MOVEMENT_REPEATS);

static const float PLATFORM_MOVEMENT_REPEATS = PLAYER_MOVEMENT_REPEATS;
static const float PLATFORM_MOVING_SPEED = 100.0f / PLAYER_MOVEMENT_REPEATS;

/* state ids */
static const int STATE_MENU = 0;
static const int STATE_GAME = 1;

/* tile ids */
/* other (not in 'tiles.png') */
static const int TILE_PLAYER_COLLIDER_FLOOR = -1;
/* main */
static const int TILE_BLOCK_ICE = 0;
static const int TILE_PLAYER = 1;
static const int TILE_STING_ICE_UP = 2;
static const int TILE_START = 3;
static const int TILE_FINISH = 4;
static const int TILE_BLOCK_BOUNCY = 5;
static const int TILE_BLOCK_STONE = 6;
static const int TILE_SPEED_UP_RIGHT = 7;
static const int TILE_SPEED_UP_LEFT = 8;
static const int TILE_SPEED_UP_UP = 9;
static const int TILE_SPEED_UP_DOWN = 10;
static const int TILE_STAR = 11;
static const int TILE_STING_ICE_DOWN = 12;
static const int TILE_STING_ICE_LEFT = 13;
static const int TILE_STING_ICE_RIGHT = 14;
static const int TILE_STING_ICE_SMALL_UP = 15;
static const int TILE_STING_ICE_SMALL_DOWN = 16;
static const int TILE_STING_ICE_SMALL_LEFT = 17;
static const int TILE_STING_ICE_SMALL_RIGHT = 18; 
static const int TILE_BLOCK_STONE_SMALL_VERTICAL = 19;
static const int TILE_BLOCK_STONE_SMALL_HORIZONTAL = 20;
static const int TILE_BLOCK_ICE_SMALL_VERTICAL = 21;
static const int TILE_BLOCK_ICE_SMALL_HORIZONTAL = 22;
static const int TILE_PLATFORM_STONE_VERTICAL = 23;
static const int TILE_PLATFORM_STONE_HORIZONTAL = 24;
static const int TILE_BLOCK_FIRE = 25;

static const int MAX_TILE_ID = TILE_BLOCK_FIRE;