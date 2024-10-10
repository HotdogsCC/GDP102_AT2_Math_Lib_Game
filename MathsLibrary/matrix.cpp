#include "matrix.h"

// Constructors
Matrix2::Matrix2()
{
	//Sets the entire matrix to 0;
	memset(this, 0, sizeof(float) * 2 * 2);
}
Matrix2::Matrix2(float _00, float _01, float _10, float _11)
{
	data[0][0] = _00;
	data[0][1] = _01;
	data[1][0] = _10;
	data[1][1] = _11;
}
Matrix2::Matrix2(const Matrix2& other)
{
	memcpy(this, &other, sizeof(float) * 2 * 2);
}

// Assignment
Matrix2& Matrix2::operator = (const Matrix2& other)
{
	memcpy(this, &other, sizeof(float) * 2 * 2);
	return *this;
}

// Indexing operators to retrieve columns
Vector2& Matrix2::operator[] (int index)
{
	return axis[index];
}
const Vector2& Matrix2::operator[] (int index) const
{
	return axis[index];
}

// Sets the matrix to an identiy matrix
void Matrix2::setIdentity()
{
	data[0][0] = 1;
	data[1][0] = 0;
	data[0][1] = 0;
	data[1][1] = 1;
}

// Returns transpose of this matrix
Matrix2 Matrix2::transposed() const
{
	Matrix2 result(*this);
	float temp = 0;

	temp = result.data[0][1];
	result.data[0][1] = result.data[1][0];
	result.data[1][0] = temp;

	return result;
}

// Returns this matrix multiplied by 'other'
Matrix2 Matrix2::operator * (const Matrix2& other) const
{
	Matrix2 result;

	result.data[0][0] = (data[0][0] * other.data[0][0]) + (data[1][0] * other.data[0][1]);
	result.data[1][0] = (data[0][0] * other.data[1][0]) + (data[1][0] * other.data[1][1]);

	result.data[0][1] = (data[0][1] * other.data[0][0]) + (data[1][1] * other.data[0][1]);
	result.data[1][1] = (data[0][1] * other.data[1][0]) + (data[1][1] * other.data[1][1]);

	return result;
}

// Multiplies other by this matrix and returns the result
Vector2 Matrix2::operator* (const Vector2& v) const
{
	Vector2 result;

	result.x = (data[0][0] * v.x) + (data[1][0] * v.y);
	result.y = (data[0][1] * v.x) + (data[1][1] * v.y);

	return result;

}

// Set the rotation
void Matrix2::setRotate(float radians)
{
	xAxis = { cosf(radians), -sinf(radians) };
	yAxis = { sinf(radians), cosf(radians) };
}

// Add to the rotation
void Matrix2::rotate(float radians)
{
	Matrix2 m;
	m.setRotate(radians);

	*this = *this * m;
}

// Set the scaled components
void Matrix2::setScaled(float x, float y)
{
	this->setIdentity();
	data[0][0] = x;
	data[1][1] = y;
}
void Matrix2::setScaled(const Vector2& v)
{
	this->setIdentity();
	data[0][0] = v.x;
	data[1][1] = v.y;
}

// Scale the scale components
void Matrix2::scale(float x, float y)
{
	Matrix2 m;
	m.setScaled(x, y);

	*this = *this * m;
}
void Matrix2::scale(const Vector2& v)
{
	Matrix2 m;
	m.setScaled(v);

	*this = *this * m;
}

//Constructors
Matrix3::Matrix3()
{
	//Sets the entire matrix to 0;
	memset(this, 0, sizeof(float) * 3 * 3);
}
Matrix3::Matrix3(float _00, float _01, float _02,
	float _10, float _11, float _12,
	float _20, float _21, float _22)
{
	data[0][0] = _00;
	data[0][1] = _01;
	data[0][2] = _02;

	data[1][0] = _10;
	data[1][1] = _11;
	data[1][2] = _12;

	data[2][0] = _20;
	data[2][1] = _21;
	data[2][2] = _22;
}
Matrix3::Matrix3(const Matrix3& other)
{
	memcpy(this, &other, sizeof(float) * 3 * 3);
}

// Assignment
Matrix3& Matrix3::operator = (const Matrix3& other)
{
	memcpy(this, &other, sizeof(float) * 3 * 3);
	return *this;
}

// Indexing operators to retrieve columns
Vector3& Matrix3::operator [] (int index)
{
	return axis[index];
}
const Vector3& Matrix3::operator[] (int index) const
{
	return axis[index];
}

// Sets the matrix to an identiy matrix
void Matrix3::setIdentity()
{
	data[0][0] = 1;
	data[0][1] = 0;
	data[0][2] = 0;

	data[1][0] = 0;
	data[1][1] = 1;
	data[1][2] = 0;

	data[2][0] = 0;
	data[2][1] = 0;
	data[2][2] = 1;
}

// Returns transpose of this matrix
Matrix3 Matrix3::transposed() const
{
	Matrix3 result(*this);
	float temp = 0;

	temp = result.data[0][1];
	result.data[0][1] = result.data[1][0];
	result.data[1][0] = temp;

	temp = result.data[0][2];
	result.data[0][2] = result.data[2][0];
	result.data[2][0] = temp;

	temp = result.data[1][2];
	result.data[1][2] = result.data[2][1];
	result.data[2][1] = temp;

	return result;
}

// Set the translation component
void Matrix3::setTranslate(float x, float y)
{
	wAxis.x = x;
	wAxis.y = y;
}
void Matrix3::setTranslate(const Vector2& other)
{
	wAxis.x = other.x;
	wAxis.y = other.y;
}

// Add to the translation component
void Matrix3::translate(float x, float y)
{
	wAxis.x += x;
	wAxis.y += y;
}
void Matrix3::translate(const Vector2& other)
{
	wAxis.x += other.x;
	wAxis.y += other.y;
}

// Set rotation using Euler representation
void Matrix3::setEuler(float pitch, float yaw, float roll)
{
	setRotateZ(roll);
	rotateY(yaw);
	rotateX(pitch);
}

// Set the rotation around X,Y and Z
void Matrix3::setRotateX(float radians)
{
	xAxis = { 1, 0, 0 };
	yAxis = { 0, cosf(radians), -sinf(radians)};
	zAxis = { 0, sinf(radians), cosf(radians)};
}
void Matrix3::setRotateY(float radians)
{
	xAxis = { cosf(radians), 0, sinf(radians) };
	yAxis = { 0, 1, 0 };
	zAxis = { -sinf(radians), 0, cosf(radians) };
}
void Matrix3::setRotateZ(float radians)
{
	xAxis = { cosf(radians), -sinf(radians), 0};
	yAxis = { sinf(radians), cosf(radians), 0 };
	zAxis = { 0, 0, 1 };
}

// Add to the rotation
void Matrix3::rotateX(float radians)
{
	Matrix3 m;
	m.setRotateX(radians);

	*this = *this * m;
}
void Matrix3::rotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);

	*this = *this * m;
}
void Matrix3::rotateZ(float radians)
{
	Matrix3 m;
	m.setRotateZ(radians);

	*this = *this * m;
}

// Set the scaled components
void Matrix3::setScaled(float x, float y, float z)
{
	this->setIdentity();
	data[0][0] = x;
	data[1][1] = y;
	data[2][2] = z;
}
void Matrix3::setScaled(const Vector3& v)
{
	this->setIdentity();
	data[0][0] = v.x;
	data[1][1] = v.y;
	data[2][2] = v.z;
}

// Scale the scale components
void Matrix3::scale(float x, float y, float z)
{
	//Scaling matrix by creating matrix with set scale, and multiplying the existing one with the scale one
	Matrix3 m;
	m.setScaled(x, y, z);

	*this = *this * m;
}
void Matrix3::scale(const Vector3& v)
{
	//Scaling matrix by creating matrix with set scale, and multiplying the existing one with the scale one
	Matrix3 m;
	m.setScaled(v.x, v.y, v.z);

	*this = *this * m;
}

// Returns this matrix multiplied by 'other'
Matrix3 Matrix3::operator * (const Matrix3& other) const
{
	Matrix3 result;

	result.data[0][0] = (data[0][0] * other.data[0][0]) + (data[1][0] * other.data[0][1]) + (data[2][0] * other.data[0][2]);
	result.data[1][0] = (data[0][0] * other.data[1][0]) + (data[1][0] * other.data[1][1]) + (data[2][0] * other.data[1][2]);
	result.data[2][0] = (data[0][0] * other.data[2][0]) + (data[1][0] * other.data[2][1]) + (data[2][0] * other.data[2][2]);

	result.data[0][1] = (data[0][1] * other.data[0][0]) + (data[1][1] * other.data[0][1]) + (data[2][1] * other.data[0][2]);
	result.data[1][1] = (data[0][1] * other.data[1][0]) + (data[1][1] * other.data[1][1]) + (data[2][1] * other.data[1][2]);
	result.data[2][1] = (data[0][1] * other.data[2][0]) + (data[1][1] * other.data[2][1]) + (data[2][1] * other.data[2][2]);

	result.data[0][2] = (data[0][2] * other.data[0][0]) + (data[1][2] * other.data[0][1]) + (data[2][2] * other.data[0][2]);
	result.data[1][2] = (data[0][2] * other.data[1][0]) + (data[1][2] * other.data[1][1]) + (data[2][2] * other.data[1][2]);
	result.data[2][2] = (data[0][2] * other.data[2][0]) + (data[1][2] * other.data[2][1]) + (data[2][2] * other.data[2][2]);

	return result;
}

// Multiplies Vector3 v by this matrix and returns the result
Vector3 Matrix3::operator * (const Vector3& v) const
{
	Vector3 result;
	result.x = (data[0][0] * v.x) + (data[1][0] * v.y) + (data[2][0] * v.z);
	result.y = (data[0][1] * v.x) + (data[1][1] * v.y) + (data[2][1] * v.z);
	result.z = (data[0][2] * v.x) + (data[1][2] * v.y) + (data[2][2] * v.z);
	return result;
}

// Constructors
Matrix4::Matrix4()
{
	//Sets the entire matrix to 0;
	memset(this, 0, sizeof(float) * 4 * 4);
}
Matrix4::Matrix4(const Matrix4& other)
{
	memcpy(this, &other, sizeof(float) * 4 * 4);
}
Matrix4::Matrix4(float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33)
{
	data[0][0] = _00;
	data[0][1] = _01;
	data[0][2] = _02;
	data[0][3] = _03;

	data[1][0] = _10;
	data[1][1] = _11;
	data[1][2] = _12;
	data[1][3] = _13;

	data[2][0] = _20;
	data[2][1] = _21;
	data[2][2] = _22;
	data[2][3] = _23;
	
	data[3][0] = _30;
	data[3][1] = _31;
	data[3][2] = _32;
	data[3][3] = _33;
}

// Assignment
Matrix4& Matrix4::operator = (const Matrix4& other)
{
	memcpy(this, &other, sizeof(float) * 4 * 4);
	return *this;
}

// Indexing operators to retrieve columns
Vector4& Matrix4::operator[] (int index)
{
	return axis[index];
}
const Vector4& Matrix4::operator[] (int index) const
{
	return axis[index];
}

// Sets matrix to an identity matrix
void Matrix4::setIdentity()
{
	memset(this, 0, sizeof(float) * 4 * 4);
	data[0][0] = 1;
	data[1][1] = 1;
	data[2][2] = 1;
	data[3][3] = 1;
}

// Returns transpose of this matrix
Matrix4 Matrix4::transposed() const
{
	Matrix4 result(*this);
	float temp = 0;

	temp = result.data[0][1];
	result.data[0][1] = result.data[1][0];
	result.data[1][0] = temp;

	temp = result.data[0][2];
	result.data[0][2] = result.data[2][0];
	result.data[2][0] = temp;

	temp = result.data[0][3];
	result.data[0][3] = result.data[3][0];
	result.data[3][0] = temp;

	temp = result.data[1][2];
	result.data[1][2] = result.data[2][1];
	result.data[2][1] = temp;

	temp = result.data[1][3];
	result.data[1][3] = result.data[3][1];
	result.data[3][1] = temp;

	temp = result.data[2][3];
	result.data[2][3] = result.data[3][2];
	result.data[3][2] = temp;

	return result;
}

// Set the translation component
void Matrix4::setTranslate(float x, float y, float z)
{
	wAxis.x = x;
	wAxis.y = y;
	wAxis.z = z;
}
void Matrix4::setTranslate(const Vector3& other)
{
	wAxis.x = other.x;
	wAxis.y = other.y;
	wAxis.z = other.z;
}

// Add to the translation component
void Matrix4::translate(float x, float y, float z)
{
	wAxis.x += x;
	wAxis.y += y;
	wAxis.z += z;
}
void Matrix4::translate(const Vector3& other)
{
	wAxis.x += other.x;
	wAxis.y += other.y;
	wAxis.z += other.z;
}

// Set rotation using Euler representation
void Matrix4::setEuler(float pitch, float yaw, float roll)
{
	setRotateZ(roll);
	rotateY(yaw);
	rotateX(pitch);
}

// Set the rotation around X,Y and Z
void Matrix4::setRotateX(float radians)
{
	xAxis = { 1, 0, 0, 0};
	yAxis = { 0, cosf(radians), -sinf(radians), 0 };
	zAxis = { 0, sinf(radians), cosf(radians), 0 };
	wAxis = { 0,0,0,1 };
}
void Matrix4::setRotateY(float radians)
{
	xAxis = { cosf(radians), 0, sinf(radians), 0 };
	yAxis = { 0, 1, 0, 0 };
	zAxis = { -sinf(radians), 0, cosf(radians), 0 };
	wAxis = { 0,0,0,1 };
}
void Matrix4::setRotateZ(float radians)
{
	xAxis = { cosf(radians), -sinf(radians), 0, 0 };
	yAxis = { sinf(radians), cosf(radians), 0, 0 };
	zAxis = { 0, 0, 1, 0 };
	wAxis = { 0,0,0,1 };
}

// Add to the rotation
void Matrix4::rotateX(float radians)
{
	Matrix4 m;
	m.setRotateX(radians);

	*this = *this * m;
}
void Matrix4::rotateY(float radians)
{
	Matrix4 m;
	m.setRotateY(radians);

	*this = *this * m;
}
void Matrix4::rotateZ(float radians)
{
	Matrix4 m;
	m.setRotateZ(radians);

	*this = *this * m;
}

// Set the scaled components
void Matrix4::setScaled(float x, float y, float z)
{
	this->setIdentity();
	data[0][0] = x;
	data[1][1] = y;
	data[2][2] = z;
}
void Matrix4::setScaled(const Vector3& v)
{
	this->setIdentity();
	data[0][0] = v.x;
	data[1][1] = v.y;
	data[2][2] = v.z;
}

// Scale the scale components
void Matrix4::scale(float x, float y, float z)
{
	Matrix4 m;
	m.setScaled(x, y, z);

	*this = *this * m;
}
void Matrix4::scale(const Vector3& v)
{
	Matrix4 m;
	m.setScaled(v.x, v.y, v.z);

	*this = *this * m;
}

// Returns this matrix multiplied by 'other'
Matrix4 Matrix4::operator * (const Matrix4& other) const
{
	Matrix4 result;

	result.data[0][0] = (data[0][0] * other.data[0][0]) + (data[1][0] * other.data[0][1]) + (data[2][0] * other.data[0][2]) + (data[3][0] * other.data[0][3]);
	result.data[1][0] = (data[0][0] * other.data[1][0]) + (data[1][0] * other.data[1][1]) + (data[2][0] * other.data[1][2]) + (data[3][0] * other.data[1][3]);
	result.data[2][0] = (data[0][0] * other.data[2][0]) + (data[1][0] * other.data[2][1]) + (data[2][0] * other.data[2][2]) + (data[3][0] * other.data[2][3]);
	result.data[3][0] = (data[0][0] * other.data[3][0]) + (data[1][0] * other.data[3][1]) + (data[2][0] * other.data[3][2]) + (data[3][0] * other.data[3][3]);

	result.data[0][1] = (data[0][1] * other.data[0][0]) + (data[1][1] * other.data[0][1]) + (data[2][1] * other.data[0][2]) + (data[3][1] * other.data[0][3]);
	result.data[1][1] = (data[0][1] * other.data[1][0]) + (data[1][1] * other.data[1][1]) + (data[2][1] * other.data[1][2]) + (data[3][1] * other.data[1][3]);
	result.data[2][1] = (data[0][1] * other.data[2][0]) + (data[1][1] * other.data[2][1]) + (data[2][1] * other.data[2][2]) + (data[3][1] * other.data[2][3]);
	result.data[3][1] = (data[0][1] * other.data[3][0]) + (data[1][1] * other.data[3][1]) + (data[2][1] * other.data[3][2]) + (data[3][1] * other.data[3][3]);

	result.data[0][2] = (data[0][2] * other.data[0][0]) + (data[1][2] * other.data[0][1]) + (data[2][2] * other.data[0][2]) + (data[3][2] * other.data[0][3]);
	result.data[1][2] = (data[0][2] * other.data[1][0]) + (data[1][2] * other.data[1][1]) + (data[2][2] * other.data[1][2]) + (data[3][2] * other.data[1][3]);
	result.data[2][2] = (data[0][2] * other.data[2][0]) + (data[1][2] * other.data[2][1]) + (data[2][2] * other.data[2][2]) + (data[3][2] * other.data[2][3]);
	result.data[3][2] = (data[0][2] * other.data[3][0]) + (data[1][2] * other.data[3][1]) + (data[2][2] * other.data[3][2]) + (data[3][2] * other.data[3][3]);

	result.data[0][3] = (data[0][3] * other.data[0][0]) + (data[1][3] * other.data[0][1]) + (data[2][3] * other.data[0][2]) + (data[3][3] * other.data[0][3]);
	result.data[1][3] = (data[0][3] * other.data[1][0]) + (data[1][3] * other.data[1][1]) + (data[2][3] * other.data[1][2]) + (data[3][3] * other.data[1][3]);
	result.data[2][3] = (data[0][3] * other.data[2][0]) + (data[1][3] * other.data[2][1]) + (data[2][3] * other.data[2][2]) + (data[3][3] * other.data[2][3]);
	result.data[3][3] = (data[0][3] * other.data[3][0]) + (data[1][3] * other.data[3][1]) + (data[2][3] * other.data[3][2]) + (data[3][3] * other.data[3][3]);

	return result;
}

// Multiplies Vector4 v by this matrix and returns the result
Vector4 Matrix4::operator * (const Vector4& v) const
{
	Vector4 result;

	result.x = (data[0][0] * v.x) + (data[1][0] * v.y) + (data[2][0] * v.z) + (data[3][0] * v.w);
	result.y = (data[0][1] * v.x) + (data[1][1] * v.y) + (data[2][1] * v.z) + (data[3][1] * v.w);
	result.z = (data[0][2] * v.x) + (data[1][2] * v.y) + (data[2][2] * v.z) + (data[3][2] * v.w);
	result.w = (data[0][3] * v.x) + (data[1][3] * v.y) + (data[2][3] * v.z) + (data[3][3] * v.w);

	return result;
}