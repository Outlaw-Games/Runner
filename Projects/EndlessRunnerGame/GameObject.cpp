#include "GameObject.h"
#include <Engine/Renderer.h>
#include <Engine/OglGame.h>

void GameObject::getRenderer(ASGE::Renderer * renderer)
{
	avatar->position[0] = posX;
	avatar->position[1] = posY;
	renderer->renderSprite(*avatar);
}