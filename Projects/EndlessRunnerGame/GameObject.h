#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include<Engine/Sprite.h>

namespace ASGE {
	class Renderer;
	class Sprite;

}


class GameObject
{
public:

	 GameObject() = default;
	 ~GameObject() = default;

	virtual bool loadAvatar(ASGE::Renderer* renderer) = 0;
	virtual ASGE::Sprite * getObject() const { return avatar; }
	virtual void GameObject::getRenderer(ASGE::Renderer* renderer);
	virtual void AddPosX(int x) = 0;
	virtual	void AddPosY(int y) = 0;
	virtual void SetPosX(int x) = 0;
	virtual void SetPosY(int y) = 0;

	virtual int getPosx() const { return posX; }
	virtual int getPosy() const { return posY; }

	ASGE::Sprite* avatar = nullptr;

protected:
	int posX;
	int posY;

private:
};
