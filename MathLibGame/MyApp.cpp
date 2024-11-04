#include "MyApp.h"
#include <iostream>
#include "Input.h"
#include "Font.h"
#include <vector>

//Generic font asset
aie::Font* m_font;

//The maze level
SpriteObject* level;
AABB* levelPhysBoxs[14];

//Player 1 Tank
SpriteObject* m_tank1; 
SpriteObject* m_turret1; 
AABB* m_physBox1;

//Player 2 Tank
SpriteObject* m_tank2;
SpriteObject* m_turret2;
AABB* m_physBox2;

//Bullets
std::vector<BulletContainer*> bullets1;
std::vector<BulletContainer*> bullets2;

//Debug mode
bool debug = false;

//Called on first frame
bool MyApp::startup() 
{
	//Assigns renderer
	m_2dRenderer = new aie::Renderer2D();

	//Assigns font
	m_font = new aie::Font("./font/consolas.ttf", 32);

	//Sets up player 1
	m_tank1 = new SpriteObject(); 
	m_tank1->load("./textures/tank.png");
	m_turret1 = new SpriteObject();
	m_turret1->load("./textures/turret.png");
	m_tank1->addChild(m_turret1);
	m_tank1->setScale(0.5f, 0.5f);
	m_tank1->setPosition(100, 150);
	m_physBox1 = new AABB();

	//Sets up player 2
	m_tank2 = new SpriteObject();
	m_tank2->load("./textures/tank2.png");
	m_turret2 = new SpriteObject();
	m_turret2->load("./textures/turret2.png");
	m_tank2->addChild(m_turret2);
	m_tank2->setScale(0.5f, 0.5f);
	m_tank2->setPosition(1130, 570);
	m_tank2->rotate(3.1415f);
	m_physBox2 = new AABB();
	
	//Sets up level
	level = new SpriteObject();
	level->load("./textures/Level.png");
	level->setScale(1.f, 1.f);
	level->setPosition(640, 360);
	//Makes a new AABB for each wall
	for (int i = 0; i < 14; i++)
	{
		levelPhysBoxs[i] = new AABB();
	}
	
	//Assigns values for the walls
	levelPhysBoxs[0]->setMinMax({180, 0}, {200, 225});
	levelPhysBoxs[1]->setMinMax({370, 0}, {390, 225});
	levelPhysBoxs[2]->setMinMax({180, 215}, {390, 225});
	levelPhysBoxs[3]->setMinMax({0, 440}, {170, 470});
	levelPhysBoxs[4]->setMinMax({110, 440}, {165, 630});
	levelPhysBoxs[5]->setMinMax({405, 540}, {445, 720});
	levelPhysBoxs[6]->setMinMax({345, 380}, {365, 540});
	levelPhysBoxs[7]->setMinMax({345, 520}, {445, 540});
	levelPhysBoxs[8]->setMinMax({ 895, 345 }, { 935, 520 });
	levelPhysBoxs[9]->setMinMax({630, 545 },{670, 720});
	levelPhysBoxs[10]->setMinMax({670, 315 },{1280, 375});
	levelPhysBoxs[11]->setMinMax({ 765, 80 }, { 1160, 110 });
	levelPhysBoxs[12]->setMinMax({ 765, 0 }, { 808, 110 });
	levelPhysBoxs[13]->setMinMax({ 1135, 80 }, { 1160, 210 });
	
	return true;
}

void MyApp::draw()
{
	// wipe the screen to the background colour
	clearScreen(); 

	// begin drawing sprites
	m_2dRenderer->begin();

	//draw level
	level->draw(m_2dRenderer);

	// draw the tank
	m_tank1->draw(m_2dRenderer); 
	m_tank2->draw(m_2dRenderer);

	//Draws debug outlines
	if (debug)
	{
		m_physBox1->debugDraw(m_2dRenderer);
		m_physBox2->debugDraw(m_2dRenderer);

		for (int i = 0; i < 14; i++)
		{
			levelPhysBoxs[i]->debugDraw(m_2dRenderer);
		}
	}
	
	//Draws the bullets for player 1
	for (auto bullet : bullets1)
	{
		if (bullet != nullptr)
		{
			bullet->bullet->draw(m_2dRenderer);

			//Draws debug outlines
			if (debug)
			{
				bullet->physBox->debugDraw(m_2dRenderer);
			}
		}
		
	}

	//Draws the bullets for player 2
	for (auto bullet : bullets2)
	{
		if (bullet != nullptr)
		{
			bullet->bullet->draw(m_2dRenderer);

			//Draws debug outlines
			if (debug)
			{
				bullet->physBox->debugDraw(m_2dRenderer);
			}
		}
	}

	//Draws text
	m_2dRenderer->drawText(m_font, "Player 1: WASD - Move, QE - Look, SPACE - Shoot", 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Player 2: IJKL - Move, UO - Look, ENTER - Shoot", 0, 720 - 64);
	m_2dRenderer->drawText(m_font, "TAB - Debug", 0, 720 - 96);
	m_2dRenderer->drawText(m_font, "R - Reset", 0, 720 - 96 - 32);

	// done drawing sprites
	m_2dRenderer->end(); 

}

//Runs when a bullet is spawned
void SpawnBullet(float posx, float posy, float dirx, float diry, bool p1)
{
	//Creates a new bullet instance
	BulletContainer* bullet = new BulletContainer();

	//Assigns transform to bullet
	bullet->bullet->setScale(0.1f, 0.1f);
	bullet->bullet->setPosition(posx, posy);
	bullet->bullet->SetDirection(dirx, diry);

	//Assigns texture and vector based on player
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

//Moves the player 1 tank
void MovePlayer1(aie::Input* input, float deltaTime)
{
	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_tank1->rotate(-deltaTime * 2);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_tank1->rotate(deltaTime * 2);

	// move tank, the 200 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		auto facing = m_tank1->getLocalTransform()[1] *
			deltaTime * 200;
		m_tank1->translate(facing.x, facing.y);

		//checks for collision with wall
		for (int i = 0; i < 14; i++)
		{
			if (m_physBox1->overlaps(*levelPhysBoxs[i]))
			{
				//Moves back if collided (conflict resoulition)
				m_tank1->translate(-facing.x*2, -facing.y*2);
			}
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		auto facing = m_tank1->getLocalTransform()[1] *
			deltaTime * -200;
		m_tank1->translate(facing.x, facing.y);

		//checks for collision
		for (int i = 0; i < 14; i++)
		{
			if (m_physBox1->overlaps(*levelPhysBoxs[i]))
			{
				//Moves back if collided (conflict resoulition)
				m_tank1->translate(-facing.x * 2, -facing.y * 2);
			}
		}
	}

	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_turret1->rotate(-deltaTime * 3);
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_turret1->rotate(deltaTime * 3);

	//Shoots a bullet
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		SpawnBullet(m_tank1->getLocalTransform().wAxis[0], m_tank1->getLocalTransform().wAxis[1], m_turret1->getGlobalTransform()[1][0], m_turret1->getGlobalTransform()[1][1], true);
	}
	
	//Set physics box min/max
	m_physBox1->setCenterSize({ m_tank1->getGlobalTransform()[2][0], m_tank1->getGlobalTransform()[2][1] }, 80);
}

void MovePlayer2(aie::Input* input, float deltaTime)
{
	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_J))
		m_tank2->rotate(-deltaTime * 2);
	if (input->isKeyDown(aie::INPUT_KEY_L))
		m_tank2->rotate(deltaTime * 2);

	// move tank, the 200 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_I)) {
		auto facing = m_tank2->getLocalTransform()[1] *
			deltaTime * 200;
		m_tank2->translate(facing.x, facing.y);

		//checks for collision
		for (int i = 0; i < 14; i++)
		{
			if (m_physBox2->overlaps(*levelPhysBoxs[i]))
			{
				//Moves back if collided (conflict resoulition)
				m_tank2->translate(-facing.x * 2, -facing.y * 2);
			}
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_K)) {
		auto facing = m_tank2->getLocalTransform()[1] *
			deltaTime * -200;
		m_tank2->translate(facing.x, facing.y);


		//checks for collision
		for (int i = 0; i < 14; i++)
		{
			if (m_physBox2->overlaps(*levelPhysBoxs[i]))
			{
				//Moves back if collided (conflict resoulition)
				m_tank2->translate(-facing.x * 2, -facing.y * 2);
			}
		}
	}

	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_U))
		m_turret2->rotate(-deltaTime * 3);
	if (input->isKeyDown(aie::INPUT_KEY_O))
		m_turret2->rotate(deltaTime * 3);

	//Shoots a bullet
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		SpawnBullet(m_tank2->getLocalTransform().wAxis[0], m_tank2->getLocalTransform().wAxis[1], m_turret2->getGlobalTransform()[1][0], m_turret2->getGlobalTransform()[1][1], false);
	}

	//Sets physics box min/max
	m_physBox2->setCenterSize({ m_tank2->getGlobalTransform()[2][0], m_tank2->getGlobalTransform()[2][1] }, 80);

}

//Called on every update, moves each bullet
void MoveBullet(std::vector<BulletContainer*> &bullets, float deltaTime, bool p1)
{
	//Loops through each bullet
	for (auto bullet : bullets)
	{
		//Moves bullet, sets AABB min/max
		bullet->bullet->translate(bullet->bullet->direction.x * bullet->bullet->speed * deltaTime, bullet->bullet->direction.y * bullet->bullet->speed * deltaTime);
		bullet->physBox->setCenterSize({ bullet->bullet->getGlobalTransform()[2][0], bullet->bullet->getGlobalTransform()[2][1] }, 10);
		
		//Destroys bullet if it hits a wall, loops each wall
		for (int i = 0; i < 14; i++)
		{
			if (bullet->physBox->overlaps(*levelPhysBoxs[i]))
			{
				bullet->bullet->setPosition(-9999, 9999);
				return;
			}
		}

		//Checks if it is player1 or 2 who shot the bullet, destroys the player if it collides
		if (p1)
		{
			if (bullet->physBox->overlaps(*m_physBox2))
			{
				//'Destroys' player by hiding
				m_tank2->setPosition(9999, 9999);
				bullet->bullet->setPosition(-9999, 9999);
			}
		}
		else
		{
			//'Destroys' player by hiding
			if (bullet->physBox->overlaps(*m_physBox1))
			{
				m_tank1->setPosition(9999, 9999);
				bullet->bullet->setPosition(-9999, 9999);
			}
		}
		
		//decays the bullet, deletes it after 3 seconds of being spawned
		if (bullet->bullet->Decay(deltaTime))
		{
			//deallocates memory
			delete bullet;

			//removes bullet
			bullets.erase(bullets.begin());

		}
		
	}

}

//Moves players to spawn positions
void ResetGame()
{
	m_tank1->setPosition(100, 150);
	m_tank2->setPosition(1130, 570);
}

//Runs every frame
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

	//resets
	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		ResetGame();
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