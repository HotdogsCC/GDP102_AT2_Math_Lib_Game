#pragma once
#include "SpriteObject.h"
class Bullet : public SpriteObject
{
public:
	void SetDirection(float x, float y);
	Vector2 direction = { 0, 0 };
	float speed = 5;
};

