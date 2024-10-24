#include "MyApp.h"
#include <iostream>
#include "Input.h"

SpriteObject* m_tank; 
SpriteObject* m_turret; 
AABB* m_physBox;

bool MyApp::startup() 
{
	m_2dRenderer = new aie::Renderer2D();

	m_tank = new SpriteObject(); 
	m_tank->load("./textures/tank.png");
	m_turret = new SpriteObject();
	m_turret->load("./textures/turret.png");

	m_tank->addChild(m_turret);

	m_tank->setPosition(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);

	Vector2 min(100.0f, 100.0f);
	Vector2 max(200.0f, 200.0f);

	m_physBox = new AABB(min, max);
	

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
	m_tank->draw(m_2dRenderer); 
	m_physBox->debugDraw(m_2dRenderer);
	// done drawing sprites
	m_2dRenderer->end(); 

}

void MyApp::update(float deltaTime)
{
	// access input
	auto input = aie::Input::getInstance();

	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_tank->rotate(-deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_tank->rotate(deltaTime);

	// move tank, the 100 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		auto facing = m_tank->getLocalTransform()[1] *
			deltaTime * 100;
		m_tank->translate(facing.x, facing.y);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		auto facing = m_tank->getLocalTransform()[1] *
			deltaTime * -100;
		m_tank->translate(facing.x, facing.y);
	}

	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_turret->rotate(-deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_turret->rotate(deltaTime);

	// draw collision
	//m_physBox->setMinMax({m_tank->getLocalTransform()[2][0], m_tank->getLocalTransform()[2][1] }, { m_tank->getLocalTransform()[2][0] + 100.0f, m_tank->getLocalTransform()[2][1] + 100.0f });
	m_physBox->setCenterSize({ m_tank->getGlobalTransform()[2][0], m_tank->getGlobalTransform()[2][1] }, 200);
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