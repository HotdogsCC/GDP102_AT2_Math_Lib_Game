#include "BulletContainer.h"

//Allocation on construction
BulletContainer::BulletContainer()
{
	bullet = new Bullet();
	physBox = new AABB();
}

//Deallocation on destruction
BulletContainer::~BulletContainer()
{
	delete bullet;
	delete physBox;
}