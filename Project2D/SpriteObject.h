#pragma once
#include "matrixTutorial.h";
class SpriteObject : public SceneObject
{
public:
	SpriteObject(){}
	SpriteObject(const char* filename) { load(filename); }
	virtual ~SpriteObject() { delete m_texture; }

	bool load(const char* filename) 
	{
		delete m_texture;
		m_texture = nullptr;
		m_texture = new aie::Texture(filename);
		return m_texture != nullptr;
	}


protected:

	aie::Texture* m_texture = nullptr;
};

