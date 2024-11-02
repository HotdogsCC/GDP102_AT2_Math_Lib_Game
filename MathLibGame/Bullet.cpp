#include "Bullet.h"

void Bullet::SetDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

bool Bullet::Decay(float deltaTime)
{
	decay -= deltaTime;

	//Returns true if bullet should be destroyed
	if (decay <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Bullet::~Bullet()
{
	//delete m_texture;
	std::cout << "gone";
}
