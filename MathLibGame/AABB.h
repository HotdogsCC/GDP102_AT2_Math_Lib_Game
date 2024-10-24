#pragma once
#include "vector.h"
#include "vector"
#include "Renderer2D.h"
class AABB
{
public:
	AABB() {}
	AABB(const Vector2& min, const Vector2& max) : m_min(min), m_max(max) {}
	Vector2 m_min, m_max;

	Vector2 center() const;
	Vector2 extents() const;

	std::vector<Vector2> corners() const;

	void debugDraw(aie::Renderer2D* renderer);

	bool overlaps(const Vector2& p) const;
	bool overlaps(const AABB& other) const;

	//Sets min and max coords
	void setMinMax(const Vector2& min, const Vector2& max);

	//Sets bounding box with center and size, assumes all sides are the same (square)
	void setCenterSize(const Vector2& center, const float size);

private:
	//utilities
	float min(float a, float b) { return a < b ? a : b; }
	float max(float a, float b) { return a > b ? a : b; }

	Vector2 min(const Vector2& a, const Vector2& b) {
		return { min(a.x, b.x), min(a.y, b.y) };
	}

	Vector2 max(const Vector2& a, const Vector2& b) {
		return { max(a.x,b.x), max(a.y, b.y) };
	}

	float clamp(float t, float a, float b) {
		return max(a, min(b, t));
	}

	Vector2 clamp(const Vector2& t, const Vector2& a, const Vector2& b) {
		return max(a, min(b, t));
	}

	Vector2 closestPoint(const Vector2& p);
};

