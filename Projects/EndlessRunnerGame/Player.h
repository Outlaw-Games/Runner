#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include <..\\Projects\EndlessRunnerGame\GameObject.h>

namespace ASGE {
	class Renderer;
	class Sprite;

}


class Player :
	public GameObject

{
public:

	Player() = default;
	~Player() = default;

	bool loadAvatar(ASGE::Renderer* renderer) override;
	void AddPosX(int x) override;
	void AddPosY(int y) override;
	void SetPosX(int x) override;
	void SetPosY(int y) override;

private:

};