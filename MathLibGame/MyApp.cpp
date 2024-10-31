#include "MyApp.h"
#include <iostream>
#include "Input.h"
#include <vector>

SpriteObject* m_tank1; 
SpriteObject* m_turret1; 
AABB* m_physBox1;

SpriteObject* m_tank2;
SpriteObject* m_turret2;
AABB* m_physBox2;

std::vector<Bullet*> bullets;

bool MyApp::startup() 
{
	m_2dRenderer = new aie::Renderer2D();

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
	m_physBox1->debugDraw(m_2dRenderer);
	m_physBox2->debugDraw(m_2dRenderer);

	for (auto bullet : bullets)
	{
		bullet->draw(m_2dRenderer);
	}
	// done drawing sprites
	m_2dRenderer->end(); 

}
void SpawnBullet(float posx, float posy, float dirx, float  diry)
{
	Bullet* bullet = new Bullet();
	bullet->load("./textures/tank.png");
	bullet->setScale(0.1f, 0.1f);
	bullet->setPosition(posx, posy);
	bullet->SetDirection(dirx, diry);
	bullets.push_back(bullet);
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

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		SpawnBullet(m_tank1->getLocalTransform().wAxis[0], m_tank1->getLocalTransform().wAxis[1], m_turret1->getGlobalTransform()[1][0], m_turret1->getGlobalTransform()[1][1]);
	}
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

	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		SpawnBullet(m_tank2->getLocalTransform().wAxis[0], m_tank2->getLocalTransform().wAxis[1], m_turret2->getGlobalTransform()[1][0], m_turret2->getGlobalTransform()[1][1]);
	}

}

void MyApp::update(float deltaTime)
{
	// access input
	auto input = aie::Input::getInstance();

	MovePlayer1(input, deltaTime);
	MovePlayer2(input, deltaTime);

	for (auto bullet : bullets)
	{
		bullet->translate(bullet->direction.x * bullet->speed, bullet->direction.y * bullet->speed);
	}
	
	//
	// SpawnBullet();

	// draw collision
	//m_physBox->setMinMax({m_tank->getLocalTransform()[2][0], m_tank->getLocalTransform()[2][1] }, { m_tank->getLocalTransform()[2][0] + 100.0f, m_tank->getLocalTransform()[2][1] + 100.0f });
	m_physBox1->setCenterSize({ m_tank1->getGlobalTransform()[2][0], m_tank1->getGlobalTransform()[2][1] }, 100);
	m_physBox2->setCenterSize({ m_tank2->getGlobalTransform()[2][0], m_tank2->getGlobalTransform()[2][1] }, 100);

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