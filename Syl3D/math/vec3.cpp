#include "vec3.h"
#include <cmath>

using namespace math;

Vec3::Vec3() 
	:
	x(0), y(0), z(0)
{}

Vec3::Vec3(float x, float y, float z)
	:
	x(x), y(y), z(z)
{}

float Vec3::mag() const {
	return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::operator + (const Vec3& other) {
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3& Vec3::operator += (const Vec3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 Vec3::operator * (float k) {
	return Vec3(x * k, y * k, z * k);
}

Vec3& Vec3::operator *= (float k) {
	x *= k;
	y *= k;
	z *= k;
	return *this;
}