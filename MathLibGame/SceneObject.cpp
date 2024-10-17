#include "SceneObject.h"
#include <cassert>
#include <iostream>

SceneObject::SceneObject()
{
	m_localTransform.setIdentity();
	m_globalTransform.setIdentity();
}

void SceneObject::addChild(SceneObject* child)
{
	//make sure it doesn't have a parent already
	assert(child->m_parent == nullptr);
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
		//unassign parent
		child->m_parent = nullptr;
	}
}

void SceneObject::update(float deltaTime) 
{
	std::cout << "i updated";
	// run onUpdate behaviour
	onUpdate(deltaTime);

	// update children
	for (auto child : m_children)
		child->update(deltaTime);
}

void SceneObject::draw(aie::Renderer2D* renderer) 
{
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
		m_globalTransform = m_parent->m_globalTransform *
			m_localTransform;
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
void SceneObject::setPosition(float x, float y) {
	m_localTransform[2] = { x, y, 1 };
	updateTransform();
}

void SceneObject::setRotate(float radians) {
	m_localTransform.setRotateZ(radians);
	updateTransform();
}

void SceneObject::setScale(float width, float height) {
	m_localTransform.setScaled(width, height, 1);
	updateTransform();
}

void SceneObject::translate(float x, float y) {
	m_localTransform.translate(x, y);
	updateTransform();
}

void SceneObject::rotate(float radians) {
	m_localTransform.rotateZ(radians);
	updateTransform();
}

void SceneObject::scale(float width, float height) {
	m_localTransform.scale(width, height, 1);
	updateTransform();
}
