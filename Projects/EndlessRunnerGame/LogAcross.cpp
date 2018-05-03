#include "LogAcross.h"


bool LogX::loadAvatar(ASGE::Renderer * renderer)
{
	avatar = renderer->createRawSprite();
	if (!avatar->loadTexture("..\\..\\Resources\\Textures\\LogAcross.png"))
	{
		return false;
	}
}

void LogX::AddPosX(int x)
{
	posX += x;
}
void LogX::AddPosY(int y)
{
	posY += y;
}

void LogX::SetPosX(int x)
{
	posX = x;
}

void LogX::SetPosY(int y)
{
	posY = y;
}