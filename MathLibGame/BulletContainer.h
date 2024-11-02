#pragma once

#include "Bullet.h"
#include "AABB.h"

class BulletContainer
{
public:
	BulletContainer();
	~BulletContainer();
	Bullet* bullet;
	AABB* physBox;
};

