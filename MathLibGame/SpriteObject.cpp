#include "SpriteObject.h"

//Loads image file
bool SpriteObject::load(const char* filename)
{
	delete m_texture;
	m_texture = nullptr;
	m_texture = new aie::Texture(filename);
	return m_texture != nullptr;
}

//Draws the sprite to the screen
void SpriteObject::onDraw(aie::Renderer2D* renderer)
{
	if (m_texture != nullptr)
	{
		renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
	}
}