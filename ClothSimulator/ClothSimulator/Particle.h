#pragma once

#include <math.h>

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

class Vector {
public:
	float x, y, z;
	Vector() : x(0), y(0), z(0) {}
	Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	Vector operator+(const Vector& op) {
		Vector v(x + op.x, y + op.y, z + op.z);
		return v;
	}

	Vector operator-(const Vector& op) {
		Vector v(x - op.x, y - op.y, z - op.z);
		return v;
	}

	void operator+=(const Vector& op) {
		x += op.x;
		y += op.y;
		z += op.z;
	}

	Vector operator*(const float& scalar) {
		Vector v(x * scalar, y * scalar, z * scalar);
		return v;
	}

	Vector operator/(const float& scalar) {
		Vector v(x / scalar, y / scalar, z / scalar);
		return v;
	}

	float GetSize() {
		return sqrt(x * x + y * y + z * z);
	}

	Vector GetUnitVector() {
		Vector v(x, y, z);
		return v / GetSize();
	}

	Vector Cross(Vector & v)
	{
		Vector vector;
		vector.x = y * v.z - z * v.y;
		vector.y = z * v.x - x * v.z;
		vector.z = x * v.y - y * v.x;
		return vector;
	}

};

class Particle {

protected:
	Vector Pos;
	Vector oldPos;
	Vector acc;
	float radius;
	float mass;

public:
	Particle(Vector _Pos, float _radius, float _mass);
	void AddForce(Vector force);
	void Update();

	void SetPos(Vector p) { 
		Pos = p;
		oldPos = p;
	}
	Vector* GetPos() { return &Pos; }
	void Draw();
	
};


#endif