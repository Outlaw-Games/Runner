#include "Movement.h"

/**< Queued Game Action. The next action to be processed as determined by user input. */
std::atomic<GameMovement> game_movement = GameMovement::NONE;