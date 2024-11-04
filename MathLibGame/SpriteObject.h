#pragma once
#include "SceneObject.h"
#include "Texture.h"
class SpriteObject : public SceneObject
{
public:

	SpriteObject() {}
	SpriteObject(const char* filename) { load(filename); }
	~SpriteObject() { delete m_texture; }

	bool load(const char* filename);

	void onDraw(aie::Renderer2D* renderer) override;

protected:

	aie::Texture* m_texture = nullptr;
};


