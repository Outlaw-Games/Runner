#pragma once
#include <string>
#include <atomic>

enum class GameMovement
{
	NONE, LEFT, RIGHT, UP, DOWN
};

extern std::atomic<GameMovement> game_movement;