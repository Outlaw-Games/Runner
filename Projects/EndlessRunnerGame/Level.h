#pragma once
#include <string>
#include <atomic>

enum class GameLevel
{
	ONE, TWO, THREE, FOUR, FIVE
};

extern std::atomic<GameLevel> game_level;