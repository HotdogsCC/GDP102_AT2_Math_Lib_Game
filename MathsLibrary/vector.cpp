#include "vector.h"

//Vector 2

//Constructors
Vector2::Vector2()
{
	x = 0;
	y = 0;
}
Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}
Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

//Assignment
Vector2& Vector2::operator = (const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

//Indexing Operators
float Vector2::operator [] (int index) const
{
	return data[index];
}
float& Vector2::operator [] (int index)
{
	return data[index];
}

//Dot product
float Vector2::dot(const Vector2& other) const
{
	return (x * other.x) + (y * other.y);
}

//Angle between
float Vector2::angleBetween(const Vector2& other) const
{
	Vector2 v1 = this->normalised();
	Vector2 v2 = other.normalised();
	float cosine = v1.dot(v2);
	return acos(cosine);
}

//True magnitude
float Vector2::magnitude() const
{
	return pow(magnitudeSqr(), 0.5f);
}

//Returns squared magnitude
float Vector2::magnitudeSqr() const
{
	return dot(*this);
}

//Normalises vector
void Vector2::normalise()
{
	*this = this->normalised();
}

//Returns normalised copy of the vector
Vector2 Vector2::normalised() const
{
	return *this / this->magnitude();
}

//Vector operations
Vector2 Vector2::operator + (const Vector2& other) const
{
	return { x + other.x, y + other.y };
}
Vector2& Vector2::operator += (const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
Vector2 Vector2::operator - (const Vector2& other) const
{
	return { x - other.x, y - other.y };
}
Vector2& Vector2::operator -= (const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

//Scalar operations
Vector2 Vector2::operator * (float scalar) const
{
	return { x * scalar, y * scalar };
}
Vector2& Vector2::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}
Vector2 Vector2::operator / (float scalar) const
{
	return { x / scalar, y / scalar };
}
Vector2& Vector2::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

//Returns true distance from one vector to another
float Vector2::distanceTo(const Vector2& other) const
{
	return pow(this->distanceToSqr(other), 0.5f);
}

//Returns squared distance from one vector to another
float Vector2::distanceToSqr(const Vector2& other) const
{
	float x1 = other.x - x;
	float y1 = other.y - y;
	return x1 * x1 + y1 * y1;
}


//Vector 3

//Constructors
Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}
Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}
Vector3::Vector3(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

//Assignment
Vector3& Vector3::operator = (const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

//Indexing operators
float Vector3::operator [] (int index) const
{
	return data[index];
}
float& Vector3::operator [] (int index)
{
	return data[index];
}

//Dot product
float Vector3::dot(const Vector3& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

//Cross product
Vector3 Vector3::cross(const Vector3& other) const
{
	float x1 = y * other.z - z * other.y;
	float y1 = z * other.x - x * other.z;
	float z1 = x * other.y - y * other.x;

	return { x1, y1, z1 };
}
static Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	float x1 = v1.y * v2.z - v1.z * v2.y;
	float y1 = v1.z * v2.x - v1.x * v2.z;
	float z1 = v1.x * v2.y - v1.y * v2.x;

	return { x1, y1, z1 };
}

// find the angle between two vectors in radians
float Vector3::angleBetween(const Vector3& other) const
{
	Vector3 v1 = this->normalised();
	Vector3 v2 = other.normalised();
	float cosine = v1.dot(v2);
	return acos(cosine);
}

// Returns the true magnitude of the vector
float Vector3::magnitude() const
{
	return pow(magnitudeSqr(), 0.5f);
}

// Returns the squared magnitude of the vector
float Vector3::magnitudeSqr() const
{
	return dot(*this);
}

// Normalises the vector
void Vector3::normalise()
{
	*this = this->normalised();
}

// Returns a normalised copy of the vector
Vector3 Vector3::normalised() const
{
	return *this / this->magnitude();
}

//Vector operations
Vector3 Vector3::operator + (const Vector3& other) const
{
	return { x + other.x, y + other.y, z + other.z };
}
Vector3& Vector3::operator += (const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
Vector3 Vector3::operator - (const Vector3& other) const
{
	return { x - other.x, y - other.y, z - other.z };
}
Vector3& Vector3::operator -= (const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

//Scalar operations
Vector3 Vector3::operator * (float scalar) const
{
	return { x * scalar, y * scalar, z * scalar };
}
Vector3& Vector3::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}
Vector3 Vector3::operator / (float scalar) const
{
	return { x / scalar, y / scalar, z / scalar };
}
Vector3& Vector3::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

//Returns true distance from one vector to another
float Vector3::distanceTo(const Vector3& other) const
{
	return pow(this->distanceToSqr(other), 0.5f);
}

//Returns squared distance from one vector to another
float Vector3::distanceToSqr(const Vector3& other) const
{
	float x1 = other.x - x;
	float y1 = other.y - y;
	float z1 = other.z - z;
	return x1 * x1 + y1 * y1 + z1 * z1;
}

//Allows casting of V3 to V4
Vector3::operator Vector4() const
{
	return { x, y, z, 0 };
}


//Vector4

//Constructors
Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}
Vector4::Vector4(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	w = d;
}
Vector4::Vector4(const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

//Assignment
Vector4& Vector4::operator = (const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

//Indexing operators
float Vector4::operator [] (int index) const
{
	return data[index];
}
float& Vector4::operator [] (int index)
{
	return data[index];
}

//Dot product
float Vector4::dot(const Vector4& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

//Angle between two vectors in radians
float Vector4::angleBetween(const Vector4& other) const
{
	Vector4 v1 = this->normalised();
	Vector4 v2 = other.normalised();
	float cosine = v1.dot(v2);
	return acos(cosine);
}

//Cross product
Vector4 Vector4::cross(const Vector4& other) const
{
	float x1 = y * other.z - z * other.y;
	float y1 = z * other.x - x * other.z;
	float z1 = x * other.y - y * other.x;

	return { x1, y1, z1, 0 };
}
static Vector4 cross(const Vector4& v1, const Vector4& v2)
{
	float x1 = v1.y * v2.z - v1.z * v2.y;
	float y1 = v1.z * v2.x - v1.x * v2.z;
	float z1 = v1.x * v2.y - v1.y * v2.x;

	return { x1, y1, z1, 0 };
}

// Returns the true magnitude of the vector
float Vector4::magnitude() const
{
	return pow(magnitudeSqr(), 0.5f);
}

// Returns the squared magnitude of the vector
float Vector4::magnitudeSqr() const
{
	return dot(*this);
}

// Normalises the vector
void Vector4::normalise()
{
	*this = this->normalised();
}

// Returns a normalised copy of the vector
Vector4 Vector4::normalised() const
{
	return *this / this->magnitude();
}

//Vector operations
Vector4 Vector4::operator + (const Vector4& other) const
{
	return { x + other.x, y + other.y, z + other.z, w + other.w };
}
Vector4& Vector4::operator += (const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}
Vector4 Vector4::operator - (const Vector4& other) const
{
	return { x - other.x, y - other.y, z - other.z, w - other.w };
}
Vector4& Vector4::operator -= (const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

//Scalar operations
Vector4 Vector4::operator * (float scalar) const
{
	return { x * scalar, y * scalar, z * scalar, w * scalar };
}
Vector4& Vector4::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}
Vector4 Vector4::operator / (float scalar) const
{
	return { x / scalar, y / scalar, z / scalar, w / scalar };
}
Vector4& Vector4::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

//Returns true distance from one vector to another
float Vector4::distanceTo(const Vector4& other) const
{
	return pow(this->distanceToSqr(other), 0.5f);
}

//Returns squared distance from one vector to another
float Vector4::distanceToSqr(const Vector4& other) const
{
	float x1 = other.x - x;
	float y1 = other.y - y;
	float z1 = other.z - z;
	float w1 = other.w - w;
	return x1 * x1 + y1 * y1 + z1 * z1 + w1 * w1;
}

//Allows casting of V4 to V3
Vector4::operator Vector3() const
{
	return { x, y, z };
}
