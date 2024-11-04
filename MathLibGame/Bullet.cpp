#include "Bullet.h"

//Sets the direction (normalised) the bullet should move in
void Bullet::SetDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

//Decays the bullet, returns tru after 3 seconds (destroying itself)
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
