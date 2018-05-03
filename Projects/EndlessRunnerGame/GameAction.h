#pragma once
#include <string>
#include <atomic>



enum class GameAction
{
	INVALID = -1, 
	NONE = 0, 
	EXIT,
	PAUSE,
	START,
	GAMEOVER,
	HOLE,
};

extern std::atomic<GameAction> game_action;