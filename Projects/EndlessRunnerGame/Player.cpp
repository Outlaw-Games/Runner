#include "Player.h"


bool Player::loadAvatar(ASGE::Renderer * renderer)
{
	avatar = renderer->createRawSprite();
	if (!avatar->loadTexture("..\\..\\Resources\\Textures\\Player.png"))
	{
		return false;
	}
}

void Player::AddPosX(int x)
{
	posX += x;
}
void Player::AddPosY(int y)
{
	posY += y;
}

void Player::SetPosX(int x)
{
	posX = x;
}

void Player::SetPosY(int y)
{
	posY = y;
}