#include "MyApp.h"
#include <iostream>
#include "Input.h"
#include "Font.h"
#include <vector>

aie::Font* m_font;
SpriteObject* m_tank1; 
SpriteObject* m_turret1; 
AABB* m_physBox1;

SpriteObject* m_tank2;
SpriteObject* m_turret2;
AABB* m_physBox2;

std::vector<BulletContainer*> bullets1;
std::vector<BulletContainer*> bullets2;

bool debug = false;

bool MyApp::startup() 
{
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_tank1 = new SpriteObject(); 
	m_tank1->load("./textures/tank.png");
	m_turret1 = new SpriteObject();
	m_turret1->load("./textures/turret.png");
	m_tank1->addChild(m_turret1);
	m_tank1->setScale(0.5f, 0.5f);
	m_tank1->setPosition(150, 150);

	m_tank2 = new SpriteObject();
	m_tank2->load("./textures/tank2.png");
	m_turret2 = new SpriteObject();
	m_turret2->load("./textures/turret2.png");
	m_tank2->addChild(m_turret2);
	m_tank2->setScale(0.5f, 0.5f);
	m_tank2->setPosition(1130, 570);
	m_tank2->rotate(3.1415f);
	

	m_physBox1 = new AABB();
	m_physBox2 = new AABB();
	

	return true;
}

void MyApp::draw()
{
	// wipe the screen to the background colour
	clearScreen(); 
	//std::cout << "drawing";
	// begin drawing sprites
	m_2dRenderer->begin();

	// draw the tank
	m_tank1->draw(m_2dRenderer); 
	m_tank2->draw(m_2dRenderer);
	if (debug)
	{
		m_physBox1->debugDraw(m_2dRenderer);
		m_physBox2->debugDraw(m_2dRenderer);
	}
	

	for (auto bullet : bullets1)
	{
		if (bullet != nullptr)
		{
			bullet->bullet->draw(m_2dRenderer);
			if (debug)
			{
				bullet->physBox->debugDraw(m_2dRenderer);
			}
		}
		
	}

	for (auto bullet : bullets2)
	{
		if (bullet != nullptr)
		{
			bullet->bullet->draw(m_2dRenderer);
			if (debug)
			{
				bullet->physBox->debugDraw(m_2dRenderer);
			}
		}
	}

	m_2dRenderer->drawText(m_font, "Player 1: WASD - Move, QE - Look, SPACE - Shoot", 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Player 2: IJKL - Move, UO - Look, ENTER - Shoot", 0, 720 - 64);
	m_2dRenderer->drawText(m_font, "TAB - Debug", 0, 720 - 96);

	// done drawing sprites
	m_2dRenderer->end(); 

}
void SpawnBullet(float posx, float posy, float dirx, float diry, bool p1)
{
	BulletContainer* bullet = new BulletContainer();

	bullet->bullet->setScale(0.1f, 0.1f);
	bullet->bullet->setPosition(posx, posy);
	bullet->bullet->SetDirection(dirx, diry);

	if (p1)
	{
		bullet->bullet->load("./textures/tank.png");
		bullets1.push_back(bullet);
	}
	else
	{
		bullet->bullet->load("./textures/tank2.png");
		bullets2.push_back(bullet);
	}
	
}

void MovePlayer1(aie::Input* input, float deltaTime)
{
	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_tank1->rotate(-deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_tank1->rotate(deltaTime);

	// move tank, the 100 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		auto facing = m_tank1->getLocalTransform()[1] *
			deltaTime * 100;
		m_tank1->translate(facing.x, facing.y);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		auto facing = m_tank1->getLocalTransform()[1] *
			deltaTime * -100;
		m_tank1->translate(facing.x, facing.y);
	}

	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_turret1->rotate(-deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_turret1->rotate(deltaTime);

	//Shoots
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		SpawnBullet(m_tank1->getLocalTransform().wAxis[0], m_tank1->getLocalTransform().wAxis[1], m_turret1->getGlobalTransform()[1][0], m_turret1->getGlobalTransform()[1][1], true);
	}
	
	//Set physics box 
	m_physBox1->setCenterSize({ m_tank1->getGlobalTransform()[2][0], m_tank1->getGlobalTransform()[2][1] }, 100);
}

void MovePlayer2(aie::Input* input, float deltaTime)
{
	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_J))
		m_tank2->rotate(-deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_L))
		m_tank2->rotate(deltaTime);

	// move tank, the 100 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_I)) {
		auto facing = m_tank2->getLocalTransform()[1] *
			deltaTime * 100;
		m_tank2->translate(facing.x, facing.y);
	}
	if (input->isKeyDown(aie::INPUT_KEY_K)) {
		auto facing = m_tank2->getLocalTransform()[1] *
			deltaTime * -100;
		m_tank2->translate(facing.x, facing.y);
	}

	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_U))
		m_turret2->rotate(-deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_O))
		m_turret2->rotate(deltaTime);

	//Shoots
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		SpawnBullet(m_tank2->getLocalTransform().wAxis[0], m_tank2->getLocalTransform().wAxis[1], m_turret2->getGlobalTransform()[1][0], m_turret2->getGlobalTransform()[1][1], false);
	}

	//Sets physics box
	m_physBox2->setCenterSize({ m_tank2->getGlobalTransform()[2][0], m_tank2->getGlobalTransform()[2][1] }, 100);

}

void MoveBullet(std::vector<BulletContainer*> &bullets, float deltaTime, bool p1)
{
	for (auto bullet : bullets)
	{
		bullet->bullet->translate(bullet->bullet->direction.x * bullet->bullet->speed * deltaTime, bullet->bullet->direction.y * bullet->bullet->speed * deltaTime);
		bullet->physBox->setCenterSize({ bullet->bullet->getGlobalTransform()[2][0], bullet->bullet->getGlobalTransform()[2][1] }, 10);
		
		if (p1)
		{
			if (bullet->physBox->overlaps(*m_physBox2))
			{
				m_tank2->setPosition(9999, 9999);

				bullet->bullet->setPosition(-9999, 9999);
			}
		}
		else
		{
			if (bullet->physBox->overlaps(*m_physBox1))
			{
				m_tank1->setPosition(9999, 9999);

				bullet->bullet->setPosition(-9999, 9999);
			}
		}
		
		//should the bullet be destoryed
		if (bullet->bullet->Decay(deltaTime))
		{
			//deallocates memory
			delete bullet;

			//removes bullet
			bullets.erase(bullets.begin());

		}
		
	}

}

void MyApp::update(float deltaTime)
{
	// access input
	auto input = aie::Input::getInstance();

	//Move players
	MovePlayer1(input, deltaTime);
	MovePlayer2(input, deltaTime);

	//Move bullets
	MoveBullet(bullets1, deltaTime, true);
	MoveBullet(bullets2, deltaTime, false);
	
	//toggle debug
	if (input->wasKeyPressed(aie::INPUT_KEY_TAB))
	{
		debug = !debug;
	}

}

int main()
{
	// allocation
	auto app = new MyApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}