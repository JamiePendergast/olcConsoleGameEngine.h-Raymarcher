#pragma once
#include <math.h>

struct sVector3 {
	double x;
	double y;
	double z;

	inline sVector3 (double x, double y, double z) : x{ x }, y{ y }, z{ z } {
	}

	sVector3 () : x{ 0.0 }, y{ 0.0 }, z{ 0.0 } {
	}

	inline sVector3 operator + (sVector3 other) {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	inline sVector3 operator - (sVector3 other) {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	inline sVector3 operator * (double scalar) {
		return {
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	inline sVector3 operator / (double scalar) {
		return {
			x / scalar,
			y / scalar,
			z / scalar
		};
	}

	inline sVector3& operator += (sVector3& other) {
		*this = *this + other;
		return *this;
	}

	inline sVector3& operator -= (sVector3& other) {
		*this = *this - other;
		return *this;
	}

	inline sVector3& operator *= (double scalar) {
		*this = *this * scalar;
		return *this;
	}

	inline sVector3& operator /= (double scalar) {
		*this = *this / scalar;
		return *this;
	}

	static inline sVector3 point (sVector3& origin, sVector3& direction, double t) {
		return origin + direction * t;
	}

	static inline double dot (sVector3 lhs, sVector3 rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	inline double sqLength ()
	{
		return fabs (sVector3::dot (*this, *this));
	}

	inline double length ()
	{
		return sqrt (fabs (sVector3::dot (*this, *this)));
	}

	inline double angle (sVector3 lhs_dir, sVector3 rhs_dir)
	{
		return acos (dot (lhs_dir, rhs_dir));
	}

	inline sVector3 normalized () {
		return *this / length ();
	}

};
