#include "MyApp.h"
#include <iostream>

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