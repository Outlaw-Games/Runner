#include "Tree.h"


bool Tree::loadAvatar(ASGE::Renderer * renderer)
{
	avatar = renderer->createRawSprite();
	if (!avatar->loadTexture("..\\..\\Resources\\Textures\\Tree.png"))
	{
		return false;
	}
}

void Tree::AddPosX(int x)
{
	posX += x;
}
void Tree::AddPosY(int y)
{
	posY += y;
}

void Tree::SetPosX(int x)
{
	posX = x;
}

void Tree::SetPosY(int y)
{
	posY = y;
}