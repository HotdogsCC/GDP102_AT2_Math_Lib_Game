#pragma once
#include <vector>
#include "Renderer2D.h"
#include "matrix.h"
class SceneObject
{
public:

	SceneObject();
	virtual ~SceneObject() {
		//detach from parent
		if (m_parent != nullptr)
		{
			m_parent->removeChild(this);
		}

		//remove all children
		for (auto child : m_children)
		{
			child->m_parent = nullptr;
		}
	}

	SceneObject* getParent() const { return m_parent; }

	size_t childCount() const { return m_children.size(); }

	SceneObject* getChild(unsigned int index) const {
		return m_children[index];
	}

	void addChild(SceneObject* child);
	void removeChild(SceneObject* child);

	virtual void onUpdate(float deltaTime) = 0;
	void update(float deltaTime);
	virtual void onDraw(aie::Renderer2D* renderer) = 0;
	void draw(aie::Renderer2D* renderer);

	const Matrix3& getLocalTransform() const;
	const Matrix3& getGlobalTransform() const;

	void updateTransform();

protected:

	SceneObject* m_parent = nullptr;
	std::vector<SceneObject*> m_children;

	Matrix3 m_localTransform;
	Matrix3 m_globalTransform;
};

