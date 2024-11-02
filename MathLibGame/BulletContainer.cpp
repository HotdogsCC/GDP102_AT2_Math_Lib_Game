#include "BulletContainer.h"

BulletContainer::BulletContainer()
{
	bullet = new Bullet();
	physBox = new AABB();
}

BulletContainer::~BulletContainer()
{
	delete bullet;
	delete physBox;
}