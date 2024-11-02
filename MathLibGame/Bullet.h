#pragma once
#include "SpriteObject.h"
class Bullet : public SpriteObject
{
public:
	void SetDirection(float x, float y); //Sets the direction the bullet moves
	bool Decay(float deltaTime); 
	~Bullet();

	Vector2 direction = { 0, 0 }; //The direction the bullet moves
	float speed = 1000; //The speed the bullet moves, pixels per second
	float decay = 3; //Seconds the bullet will remain before despawning
};


