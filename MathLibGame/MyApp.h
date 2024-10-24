#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "SpriteObject.h"
#include "AABB.h"
class MyApp : public aie::Application
{
public:
	MyApp() {}
	virtual ~MyApp() {}

	virtual bool startup();
	virtual void shutdown() {}

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	aie::Renderer2D* m_2dRenderer;
};

