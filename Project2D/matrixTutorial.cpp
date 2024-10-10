#include "matrixTutorial.h"

void SceneObject::addChild(SceneObject* child)
{
	//assign this as parent
	child->m_parent = this;
	//add new child to collection
	m_children.push_back(child);
}

void SceneObject::removeChild(SceneObject* child)
{
	//find the child in the collection
	auto iter = std::find(m_children.begin(), m_children.end(), child);

	//if found, remove it
	if (iter != m_children.end())
	{
		m_children.erase(iter);
		// unassign parent
		child->m_parent = nullptr;
	}
}

void SceneObject::update(float deltaTime)
{
	// run onUpdate behaviour
	onUpdate(deltaTime);

	// update children
	for (auto child : m_children)
		child->update(deltaTime);

}

void SceneObject::draw(aie::Renderer2D* renderer) {
	// run onDraw behaviour
	onDraw(renderer);

	// draw children
	for (auto child : m_children)
		child->draw(renderer);
}

const Matrix3& SceneObject::getLocalTransform() const {
	return m_localTransform;
}

const Matrix3& SceneObject::getGlobalTransform() const {
	return m_globalTransform;
}

void SceneObject::updateTransform()
{
	if (m_parent != nullptr)
	{
		//Sets our global transform to the parents global * our local, 
		// as multiplying matrices combines their effects
		m_globalTransform = m_parent->m_globalTransform * m_localTransform;
	}
	else
	{
		m_globalTransform = m_localTransform;
	}

	for (auto child : m_children)
	{
		child->updateTransform();
	}
}
