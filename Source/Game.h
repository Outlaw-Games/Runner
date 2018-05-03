#pragma once
#include <atomic>
#include <Engine\OGLGame.h>
#include <..\\Projects\EndlessRunnerGame\GameObject.h>
#include <..\\Projects\EndlessRunnerGame\Player.h>
#include <..\\Projects\EndlessRunnerGame\Tree.h>
#include <..\\Projects\EndlessRunnerGame\LogAcross.h>
#include <..\\Projects\EndlessRunnerGame\LogDown.h>

namespace ASGE {
	struct GameTime;
}

/**
*  EndlessGame is the main entrypoint into the game.
*  It is based on the ASGE framework and makes use of
*  the OGLGame class. This allows the rendering and
*  input initialisation to be handled easily and without
*  fuss. The game logic responsible for updating and 
*  rendering the game starts here. 
*/
class EndlessGame : 
	public ASGE::OGLGame
{
public:

	/**
	*  Default constructor for game.
	*/
	EndlessGame() = default;
	
	/**
	*  Destructor for game.
	*  Make sure to clean up any dynamically allocated
	*  memory inside the game's destructor. For example
	*  game fonts need to be deallocated. 
	*/
	~EndlessGame();

	/**
	*  The initialisation of the game.
	*  Both the game's initialisation and the API setup
	*  should be performed inside this function. Once the 
	*  API is up and running the input system can register
	*  callback functions when certain events happen. 
	*/
	virtual bool init() override;
	Player* player = nullptr;
	Tree* tree = nullptr;
	LogX* log_across = nullptr;
	LogDown* log_down = nullptr;
	Tree* tree2 = nullptr;

	void processGameMovement();
	void processGameActions();
	void processGameLevel();
	void Score();
	void ProcessScore();
private:
	/**
	*  The simulation for the game.
	*  The objects in the game need to updated or simulated
	*  over time. Use this function to decouple the render
	*  phases from the simulation.
	*  @param us The delta time between frames and running time
	*  @see GameTime
	*/
	virtual void update(const ASGE::GameTime & us) override;
	
	/**
	*  The rendering of the game.
	*  This function gets called after the game world has 
	*  been updated. Ensure all your objects are in a sane
	*  simulated state before calling this function.
	*  @param us The delta time between frames and running time
	*  @see GameTime
	*/
	virtual void render(const ASGE::GameTime & us) override;
	
	/**
	*  The key handling function for the game.
	*  Key inputs will be delivered and handled within this function.
	*  Make a decision whether to process the input immediately
	*  or whether to generate a queue of actions that are then
	*  processed at the beginning of the game update loop.
	*  @param data They key event and its related data. 
	*  @see SharedEventData
	*/
	void keyHandler(ASGE::SharedEventData data);

	int key_handler_id = -1;  /**< Input Callback ID. The callback ID assigned by the game engine. */
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	bool pause = false;
	bool start = false;
	bool GameOver = false;
	bool level1 = true;
	bool level2 = false;
	bool level3 = false;
	bool level4 = false;
	bool level5 = false;
	bool TreeCollision(int ix, int iy, int jx, int jy);
	bool LogDownCollision(int ax, int ay, int bx, int by);
	bool LogAcrossCollision(int ax, int ay, int bx, int by);
	bool TreeCollision2(int cx, int cy, int djx, int dy);
	int score = 0;
	int endscore = score;
	int highscore;

};