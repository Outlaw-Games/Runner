#include "LogDown.h"


bool LogDown::loadAvatar(ASGE::Renderer * renderer)
{
	avatar = renderer->createRawSprite();
	if (!avatar->loadTexture("..\\..\\Resources\\Textures\\LogDown.png"))
	{
		return false;
	}
}

void LogDown::AddPosX(int x)
{
	posX += x;
}
void LogDown::AddPosY(int y)
{
	posY += y;
}

void LogDown::SetPosX(int x)
{
	posX = x;
}

void LogDown::SetPosY(int y)
{
	posY = y;
}