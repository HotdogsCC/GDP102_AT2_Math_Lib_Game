#pragma once
#include "Application2D.h"
class My2DApp : public aie::Application
{
public:
	My2DApp();
	virtual ~My2DApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D* m_2dRenderer;
};

