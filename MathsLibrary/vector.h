/*
 * 
 * Instructions to students. 
 * Use this file as the header to complete your vector2, vector3 and vector4 classes.
 * You will have to fill out the data members for each class in this file, and then provide the function definitions in a separate cpp file.
 * 
 */

#pragma once

#ifndef __VECTOR_HEADER
#define __VECTOR_HEADER

//class Vector4;

#include <iostream>

/*
 * VECTOR 2
 */
class Vector2 {
public:
	//Vector components here
	union
	{
		struct
		{
			float x, y;
		};
		struct
		{
			float data[2];
		};
	};
	// Constructors
	Vector2();
	Vector2(float _x, float _y);
	Vector2(const Vector2& other);

	// Assignment
	Vector2& operator = (const Vector2& other);

	// Indexing operators
	float operator [] (int index) const;

	float& operator [] (int index);

	// Dot product
	float dot(const Vector2& other) const;

	// find the angle between two vectors in radians
	float angleBetween(const Vector2& other) const;
	
	// Returns the true magnitude of the vector
	float magnitude() const;

	// Returns the squared magnitude of the vector
	float magnitudeSqr() const;

	// Normalises the vector
	void normalise();

	// Returns a normalised copy of the vector
	Vector2 normalised() const;

	//Vector operations
	Vector2 operator + (const Vector2& other) const;
	Vector2& operator += (const Vector2& other);
	Vector2 operator - (const Vector2& other) const;
	Vector2& operator -= (const Vector2& other);

	//Scalar operations
	Vector2 operator * (float scalar) const;
	Vector2& operator *= (float scalar);
	Vector2 operator / (float scalar) const;
	Vector2& operator /= (float scalar);

	// Returns true distance from one vector position to another.
	float distanceTo(const Vector2& other) const;

	// Returns squared distance from one vector position to another.
	float distanceToSqr(const Vector2& other) const;

	// Convenience function declaration, provide implementation in the cpp file.
	// If the vector contains 2,-1.5 should output "2,-1.5" to the console
	friend std::ostream& operator << (std::ostream& os, const Vector2& v) 
	{
		os << v.x << ',' << v.y; return os;
	}
};


// END VECTOR2


/*
 * VECTOR 3
 */
class Vector4;

class Vector3 {
public:
	// Vector components
	union
	{
		struct
		{
			float x, y;
			union
			{
				float z, w;
			};
		};
		struct
		{
			float r, b, g;
		};
		struct
		{
			float data[3];
		};
	};
	// Constructors
	Vector3();
	Vector3(float a, float b, float c);
	Vector3(const Vector3& other);

	// Assignment
	Vector3& operator = (const Vector3& other);

	// Indexing operators
	float operator [] (int index) const;

	float& operator [] (int index);

	// Dot product
	float dot(const Vector3& other) const;
	
	// Cross product
	Vector3 cross(const Vector3& other) const;
	static Vector3 cross(const Vector3& v1, const Vector3& v2);

	// find the angle between two vectors in radians
	float angleBetween(const Vector3& other) const;
	
	// Returns the true magnitude of the vector
	float magnitude() const;

	// Returns the squared magnitude of the vector
	float magnitudeSqr() const;

	// Normalises the vector
	void normalise();

	// Returns a normalised copy of the vector
	Vector3 normalised() const;

	//Vector operations
	Vector3 operator + (const Vector3& other) const;
	Vector3& operator += (const Vector3& other);
	Vector3 operator - (const Vector3& other) const;
	Vector3& operator -= (const Vector3& other);

	//Scalar operations
	Vector3 operator * (float scalar) const;
	Vector3& operator *= (float scalar);
	Vector3 operator / (float scalar) const;
	Vector3& operator /= (float scalar);


	// Returns true distance from one vector position to another.
	float distanceTo(const Vector3& other) const;

	// Returns squared distance from one vector position to another.
	float distanceToSqr(const Vector3& other) const;

	friend std::ostream& operator << (std::ostream& os, const Vector3& v) 
	{
		os << v.x << ',' << v.y << ',' << v.z; return os;
	}

	operator Vector4() const;
};


// END VECTOR3


/*
 * VECTOR 4
 */
class Vector4 {
public:
	// Vector components
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, b, g, a;
		};
		struct
		{
			float data[4];
		};
	};
	// Constructors
	Vector4();
	Vector4(float a, float b, float c, float d);
	Vector4(const Vector4& other);

	// Assignment
	Vector4& operator = (const Vector4& other);

	// Indexing operators
	float operator [] (int index) const;

	float& operator [] (int index);

	// Dot product
	float dot(const Vector4& other) const;

	// find the angle between two vectors in radians
	float angleBetween(const Vector4& other) const;

	// Cross product
	Vector4 cross(const Vector4& other) const;

	// Returns the true magnitude of the vector
	float magnitude() const;

	// Returns the squared magnitude of the vector
	float magnitudeSqr() const;

	// Normalises the vector
	void normalise();

	// Returns a normalised copy of the vector
	Vector4 normalised() const;

	//Vector operations
	Vector4 operator + (const Vector4& other) const;
	Vector4& operator += (const Vector4& other);
	Vector4 operator - (const Vector4& other) const;
	Vector4& operator -= (const Vector4& other);

	//Scalar operations
	Vector4 operator * (float scalar) const;
	Vector4& operator *= (float scalar);
	Vector4 operator / (float scalar) const;
	Vector4& operator /= (float scalar);

	// Returns true distance from one vector position to another.
	float distanceTo(const Vector4& other) const;

	// Returns squared distance from one vector position to another.
	float distanceToSqr(const Vector4& other) const;

	friend std::ostream& operator << (std::ostream& os, const Vector4& v) {
		os << v.x << ',' << v.y << ',' << v.z << ',' << v.w; return os;
	}
	operator Vector3() const;
};

// END VECTOR4

#endif