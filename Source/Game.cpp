#include <Engine\GameTime.h>
#include <Engine\InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/Sprite.h>
#include <string>
#include "Game.h"
#include "GameFont.h"
#include <..\\Projects\EndlessRunnerGame\GameObject.h>
#include <..\\Projects\EndlessRunnerGame\Player.h>
#include <..\\Projects\EndlessRunnerGame\Movement.h>
#include <..\\Projects\EndlessRunnerGame\GameAction.h>
#include <..\\Projects\EndlessRunnerGame\Tree.h>
#include <..\\Projects\EndlessRunnerGame\LogDown.h>
#include <..\\Projects\EndlessRunnerGame\LogAcross.h>
#include <../Projects/EndlessRunnerGame/Level.h>
#include <iostream>
#include <fstream>

EndlessGame::~EndlessGame()
{
	this->inputs->unregisterCallback(key_handler_id);

	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}
	if (player)
	{
		delete player;
		player = nullptr;
	}
	if (tree)
	{
		delete player;
		player = nullptr;
	}
	if (tree2)
	{
		delete player;
		player = nullptr;
	}
	if (log_across)
	{
		delete player;
		player = nullptr;
	}
	if (log_down)
	{
		delete player;
		player = nullptr;
	}
}



bool EndlessGame::TreeCollision(int ix, int iy, int jx, int jy)
{
	// 50 is the width and height of the player and tree sprites
	if (ix < jx + 50 &&
		ix + 50 > jx &&
		iy < jy + 50 &&
		iy + 50 > jy)
	{
		return true;
	}
	else
	{
		return false;
	}


}
bool EndlessGame::TreeCollision2(int cx, int cy, int dx, int dy)
{
	// 50 is the width and height of the player and tree sprites
	if (cx < dx + 50 &&
		cx + 50 > dx &&
		cy < dy + 50 &&
		cy + 50 > dy)
	{
		return true;
	}
	else
	{
		return false;
	}


}

bool EndlessGame::LogDownCollision(int ax, int ay, int bx, int by)
{
	// 50 is the width and height of the player and tree sprites
	if (ax < bx + 50 &&
		ax + 50 > bx &&
		ay < by + 100 &&
		ay + 50 > by)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool EndlessGame::LogAcrossCollision(int ex, int ey, int fx, int fy)
{
	// 50 is the width and height of the player and tree sprites
	if (ex < fx + 100 &&
		ex + 50 > fx &&
		ey < fy + 50 &&
		ey + 50 > fy)
	{
		return true;
	}
	else
	{
		return false;
	}


}

bool EndlessGame::init()
{
	game_width = 1280;
	game_height = 720;

	if (!initAPI(ASGE::Renderer::WindowMode::WINDOWED))
	{
		return false;
	}
	
	std::string read_file;
	std::ifstream myfile2;
	myfile2.open("..\\..\\highscore.txt");
	if (myfile2 >> read_file)
	{
		highscore = std::stoi(read_file);
		myfile2.close();
	}
	

	player = new Player();
	player->loadAvatar(renderer.get());
	

	tree = new Tree();
	tree->loadAvatar(renderer.get());
	tree->SetPosX(1235);
	tree->SetPosY(rand()%game_height);

	tree2 = new Tree();
	tree2->loadAvatar(renderer.get());
	tree2->SetPosX(1235);
	tree2->SetPosY(rand() % game_height);
	
	log_across = new LogX();
	log_across->loadAvatar(renderer.get());
	log_across->SetPosX(1235);
	log_across->SetPosY(rand() % game_height);

	log_down = new LogDown();
	log_down->loadAvatar(renderer.get());
	log_down->SetPosX(1235);
	log_down->SetPosY(rand() % game_height);


	renderer->setWindowTitle("Endless Runner");

	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
	toggleFPS();

	

	this->inputs->use_threads = false;
	this->inputs->addCallbackFnc(
		ASGE::EventType::E_KEY, &EndlessGame::keyHandler, this);

	return true;
}

void EndlessGame::update(const ASGE::GameTime& us)
{
	processGameMovement();
	processGameActions();
	processGameLevel();
	Score();
	ProcessScore();

	if (start == true)
	{
		if (level1 == true)
		{
			tree->AddPosX(-1);
			log_down->AddPosX(-1);
			tree2->AddPosX(-1);
		}
		if (level2 == true)
		{
			tree->AddPosX(-1.5);
			log_down->AddPosX(-1.5);
			tree2->AddPosX(-1.5);
		}
		if (level3 == true)
		{
			tree->AddPosX(-2);
			log_down->AddPosX(-2);
			tree2->AddPosX(-2);
			log_across->AddPosX(-2);
		}
		if (level4 == true)
		{
			tree->AddPosX(-2.5);
			log_down->AddPosX(-2.5);
			tree2->AddPosX(-2.5);
			log_across->AddPosX(-2.5);
		}
		if (level5 == true)
		{
			tree->AddPosX(-3);
			log_down->AddPosX(-3);
			tree2->AddPosX(-3);
			log_across->AddPosX(-3);
		}
		if (up == true)
		{
			player->AddPosY(-1);

		}
		if (down == true)
		{
			player->AddPosY(+1.f);

		}
		if (right == true)
		{
			player->AddPosX(+1.f);

		}
		if (left == true)
		{
			player->AddPosX(-1.f);

		}
		if (pause == true)
		{
			right = false;
			left = false;
			up = false;
			down = false;
			pause = true;

		}
			if (TreeCollision(player->getPosx(), player->getPosy(), tree->getPosx(), tree->getPosy()))
			{
				
				GameOver = true;
				game_action = GameAction::GAMEOVER;
			}
			if (TreeCollision(player->getPosx(), player->getPosy(), tree2->getPosx(), tree2->getPosy()))
			{

				GameOver = true;
				game_action = GameAction::GAMEOVER;
			}
			if (LogDownCollision(player->getPosx(), player->getPosy(), log_down->getPosx(), log_down->getPosy()))
			{

				GameOver = true;
				game_action = GameAction::GAMEOVER;
			}
			if (LogAcrossCollision(player->getPosx(), player->getPosy(), log_across->getPosx(), log_across->getPosy()))
			{

				GameOver = true;
				game_action = GameAction::GAMEOVER;
			}
			if (tree->getPosx() <= 0)
			{
				tree->SetPosX(1235);
				tree->SetPosY(rand() % game_height-50);
			}
			if (tree2->getPosx() <= 0)
			{
				tree2->SetPosX(1235);
				tree2->SetPosY(rand() % game_height-50);
			}
			if (log_down->getPosx() <= 0)
			{
				log_down->SetPosX(1235);
				log_down->SetPosY(rand() % game_height-100);
			}
			if (log_across->getPosx() <= 0)
			{
				log_across->SetPosX(1235);
				log_across->SetPosY(rand() % game_height - 50);
			}
	}
	game_action = GameAction::NONE;

}
void EndlessGame::render(const ASGE::GameTime& us)
{

	if (GameOver == false)
	{

		if (start == false)
		{
			renderer->renderText("ENDLESS RUNNER", 200, 325, 1.0, ASGE::COLOURS::RED);
			renderer->renderText("Press Enter to Start", 375, 325, 1.0, ASGE::COLOURS::BLUE);
			renderer->setClearColour(ASGE::COLOURS::BLACK);
		}
		if (start == true)
		{

			renderer->setClearColour(ASGE::COLOURS::GREEN);
			player->getRenderer(renderer.get());

			std::string s_score = std::to_string(score);
			char const *score_1 = s_score.c_str();
			renderer->renderText("SCORE = ", 10, 630, 0.5, ASGE::COLOURS::LIGHTYELLOW);
			renderer->renderText(score_1, 85, 630, 0.5, ASGE::COLOURS::BLUE);


			std::string s_debug_1 = std::to_string(player->getPosx());
			char const *test_1 = s_debug_1.c_str();
			renderer->renderText("DEBUG = ", 10, 610, 0.5, ASGE::COLOURS::LIGHTYELLOW);
			renderer->renderText(test_1, 85, 610, 0.5, ASGE::COLOURS::BLUE);

			std::string s_debug_2 = std::to_string(player->getPosy());
			char const *test_2 = s_debug_2.c_str();
			renderer->renderText("DEBUG = ", 10, 620, 0.5, ASGE::COLOURS::LIGHTYELLOW);
			renderer->renderText(test_2, 85, 620, 0.5, ASGE::COLOURS::BLUE);
			
			if (level1 == true)
			{
				renderer->renderText("Level 1", 10, 640, 0.5, ASGE::COLOURS::LIGHTYELLOW);
				tree->getRenderer(renderer.get());
				log_down->getRenderer(renderer.get());
				tree2->getRenderer(renderer.get());
			}
			if (level2 == true)
			{
				renderer->renderText("Level 2", 10, 640, 0.5, ASGE::COLOURS::LIGHTYELLOW);
				tree->getRenderer(renderer.get());
				log_down->getRenderer(renderer.get());
				tree2->getRenderer(renderer.get());
				
			}
			if (level3 == true)
			{
				renderer->renderText("Level 3", 10, 640, 0.5, ASGE::COLOURS::LIGHTYELLOW);
				tree->getRenderer(renderer.get());
				log_down->getRenderer(renderer.get());
				tree2->getRenderer(renderer.get());
				log_across->getRenderer(renderer.get());

			}
			if (level4 == true)
			{
				renderer->renderText("Level 4", 10, 640, 0.5, ASGE::COLOURS::LIGHTYELLOW);
				tree->getRenderer(renderer.get());
				log_down->getRenderer(renderer.get());
				tree2->getRenderer(renderer.get());
				log_across->getRenderer(renderer.get());

			}
			if (level5 == true)
			{
				renderer->renderText("Level 5 = ", 10, 640, 0.5, ASGE::COLOURS::LIGHTYELLOW);
				tree->getRenderer(renderer.get());
				log_down->getRenderer(renderer.get());
				tree2->getRenderer(renderer.get());
				log_across->getRenderer(renderer.get());

			}
		}
	}

	if (GameOver == true)
	{
		if (score > highscore)
		{
			std::ofstream myfile;
			myfile.open("..\\..\\highscore.txt");
			myfile << score;
			myfile.close();
		}

		renderer->setClearColour(ASGE::COLOURS::BLACK);
		renderer->renderText("Game Over", 375, 325, 1.0, ASGE::COLOURS::BLUE);
		std::string s_score = std::to_string(score);
		char const *score_1 = s_score.c_str();
		renderer->renderText("SCORE = ", 10, 345, 1.0, ASGE::COLOURS::LIGHTYELLOW);
		renderer->renderText(score_1, 105, 345, 1.0, ASGE::COLOURS::BLUE);

		std::string s_highscore = std::to_string(highscore);
		char const *highscore_1 = s_highscore.c_str();
		renderer->renderText("HIGHSCORE = ", 10, 400, 1.0, ASGE::COLOURS::LIGHTYELLOW);
		renderer->renderText(highscore_1, 150, 400, 1.0, ASGE::COLOURS::BLUE);

	}
	
}

void EndlessGame::keyHandler(const ASGE::SharedEventData data)
{
	const ASGE::KeyEvent* key_event =
		static_cast<const ASGE::KeyEvent*>(data.get());

	auto key = key_event->key;
	auto action = key_event->action;
	if (action == ASGE::KEYS::KEY_PRESSED)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			signalExit();
		}
		if (key == ASGE::KEYS::KEY_W)
		{
			game_movement = GameMovement::UP;
		}
		if (key == ASGE::KEYS::KEY_S)
		{
			game_movement = GameMovement::DOWN;
		}
		if (key == ASGE::KEYS::KEY_A)
		{
			game_movement = GameMovement::LEFT;
		}
		if (key == ASGE::KEYS::KEY_D)
		{
			game_movement = GameMovement::RIGHT;
		}
		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_action = GameAction::START;
		}
		if (key == ASGE::KEYS::KEY_0)
		{
			game_action = GameAction::GAMEOVER;
		}
		if (key == ASGE::KEYS::KEY_1)
		{
			game_level = GameLevel::ONE;
		}
		if (key == ASGE::KEYS::KEY_2)
		{
			game_level = GameLevel::TWO;
		}
		if (key == ASGE::KEYS::KEY_3)
		{
			game_level = GameLevel::THREE;
		}
		if (key == ASGE::KEYS::KEY_4)
		{
			game_level = GameLevel::FOUR;
		}
		if (key == ASGE::KEYS::KEY_5)
		{
			game_level = GameLevel::FIVE;
		}
		if (key == ASGE::KEYS::KEY_SPACE)
		{
			start == false;
			game_action = GameAction::NONE;

		}
		if (key == ASGE::KEYS::KEY_P)
		{

			if (game_action != GameAction::PAUSE)
			{
				game_action = GameAction::PAUSE;
			}
			else if (game_action == GameAction::PAUSE)
			{
				game_action = GameAction::NONE;

			}
		}

	}
}


void EndlessGame::processGameMovement()
{
	if (game_movement == GameMovement::UP)
	{
		down = false;
		up = true;
		right = false;
		left = false;
		pause = false;

	}
	if (game_movement == GameMovement::DOWN)
	{
		up = false;
		down = true;
		right = false;
		left = false;
		pause = false;
	}
	if (game_movement == GameMovement::LEFT)
	{
		left = true;
		up = false;
		down = false;
		right = false;
		pause = false;
	}
	if (game_movement == GameMovement::RIGHT)
	{
		right = true;
		left = false;
		up = false;
		down = false;
		pause = false;
	}
	if (game_action == GameAction::PAUSE)
	{
		right = false;
		left = false;
		up = false;
		down = false;
		pause = true;
	}
}

void EndlessGame::processGameActions()
{
	if (game_action == GameAction::EXIT)
	{
		exit = true;
	}
	if (game_action == GameAction::START)
	{
		this->start = true;

	}
	if (game_action == GameAction::GAMEOVER)
	{
		GameOver = true;

	}



}

void EndlessGame::processGameLevel()
{
	if (game_level == GameLevel::ONE)
	{
		level1 = true;
	}
	if (game_level == GameLevel::TWO)
	{
		level2 = true;
	}
	if (game_level == GameLevel::THREE)
	{
		level3 = true;
	}
	if (game_level == GameLevel::FOUR)
	{
		level4 = true;
	}
	if (game_level == GameLevel::FIVE)
	{
		level5 = true;
	}
}

void EndlessGame::Score()
{
	if (start == true && GameOver == false)
	{
		score = score + 1;
	}
	if (GameOver == true)
	{
	//here

		endscore = score;
	}
}

void EndlessGame::ProcessScore()
{
	if (score == 10000)
	{
		level2 = true;
	}
	if (score == 30000)
	{
		level3 = true;
	}
	if (score == 50000)
	{
		level4 = true;
	}
	if (score == 80000)
	{
		level5 = true;
	}
}

