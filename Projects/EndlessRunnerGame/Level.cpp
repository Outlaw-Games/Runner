#include "Level.h"

/**< Queued Game Action. The next action to be processed as determined by user input. */
std::atomic<GameLevel> game_level = GameLevel::ONE;