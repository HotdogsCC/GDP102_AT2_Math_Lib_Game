#include "MyApp.h"
#include <iostream>
#include "Input.h"

SpriteObject* m_tank; 
SpriteObject* m_turret; 

bool MyApp::startup() 
{
	m_2dRenderer = new aie::Renderer2D();

	m_tank = new SpriteObject(); 
	m_tank->load("./textures/tank.png");
	m_turret = new SpriteObject();
	m_turret->load("./textures/turret.png");

	m_tank->addChild(m_turret);

	m_tank->setPosition(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);

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
		std::cout << m_tank->getLocalTransform()[1];
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