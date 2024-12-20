#include "AABB.h"

//Returns the center of the AABB
Vector2 AABB::center() const {
	return (m_min + m_max) * 0.5f;
}

//Returns the extents of the AABB
Vector2 AABB::extents() const {
	return { abs(m_max.x - m_min.x) * 0.5f,
	abs(m_max.y - m_min.y) * 0.5f };
}

//Returns the corners of the AABB
std::vector<Vector2> AABB::corners() const {
	std::vector<Vector2> corners(4);
	corners[0] = m_min;
	corners[1] = { m_min.x, m_max.y };
	corners[2] = m_max;
	corners[3] = { m_max.x, m_min.y };
	return corners;

}

//Draws the outline around the AABB
void AABB::debugDraw(aie::Renderer2D* renderer)
{
	renderer->drawLine(m_min.x, m_min.y, m_max.x, m_min.y);
	renderer->drawLine(m_max.x, m_min.y, m_max.x, m_max.y);
	renderer->drawLine(m_max.x, m_max.y, m_min.x, m_max.y);
	renderer->drawLine(m_min.x, m_max.y, m_min.x, m_min.y);

}

//Checks for overlap with a 2D point
bool AABB::overlaps(const Vector2& p) const {
	// test for not overlapped as it exits faster
	return !(p.x < m_min.x || p.y < m_min.y ||
		p.x > m_max.x || p.y > m_max.y);

}

//Checks for overlap with another AABB
bool AABB::overlaps(const AABB& other) const {
	// test for not overlapped as it exits faster
	return !(m_max.x < other.m_min.x || m_max.y < other.m_min.y ||
		m_min.x > other.m_max.x || m_min.y > other.m_max.y);
}

//Returns point on the AABB closest to a given point p
Vector2 AABB::closestPoint(const Vector2& p){
	return clamp(p, m_min, m_max); 
}

//Sets min and max for the AABB
void AABB::setMinMax(const Vector2& min, const Vector2& max)
{
	m_min = min;
	m_max = max;
}

//Sets bounding box with center and size, assumes all sides are the same (square)
void AABB::setCenterSize(const Vector2& center, const float size)
{
	m_min = { center.x - (size * 0.5f), center.y - (size * 0.5f) };
	m_max = { center.x + (size * 0.5f), center.y + (size * 0.5f) };
}