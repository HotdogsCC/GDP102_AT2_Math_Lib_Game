#pragma once
#include "SceneObject.h"
#include "Texture.h"
class SpriteObject : public SceneObject
{
public:

	SpriteObject() {}
	SpriteObject(const char* filename) { load(filename); }
	~SpriteObject() { delete m_texture; }

	bool load(const char* filename) {
		delete m_texture;
		m_texture = nullptr;
		m_texture = new aie::Texture(filename);
		return m_texture != nullptr;
	}

	void onDraw(aie::Renderer2D* renderer) override
	{
		if (m_texture != nullptr)
		{
			renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
		}
	}

protected:

	aie::Texture* m_texture = nullptr;
};


