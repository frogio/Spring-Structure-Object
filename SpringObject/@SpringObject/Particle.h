#pragma once
#include <math.h>
#define PI 3.141592


class Vector2D {

public:
	float x, y;

	Vector2D() : x(0), y(0) {}

	Vector2D(float _x, float _y)
		: x(_x), y(_y){}

	Vector2D operator+(const Vector2D& _v) {
		Vector2D v(this->x + _v.x, this->y + _v.y);
		return v;
	}

	Vector2D operator-(const Vector2D & _v){
		Vector2D v(this->x - _v.x, this->y - _v.y);
		return v;
	}

	Vector2D & operator=(const Vector2D& _v) {
		this->x = _v.x, this->y = _v.y;
		return *this;
	}

	Vector2D operator*(const float scalar) {
		Vector2D v(this->x * scalar, this->y * scalar);
		return v;
	}

	Vector2D operator/(const float scalar) {
		Vector2D v(this->x / scalar, this->y / scalar);
		return v;
	}
	
	float GetSize() {
		return sqrt(x * x + y * y);
	}

	Vector2D GetUnitVector() {
		return Vector2D(x / GetSize(), y / GetSize());
	}

	float GetX() {
		return x;
	}

	float GetY() {
		return y;
	}
};

class Particle {
private:
	Vector2D position;
	Vector2D old_position;
	float mass;
	Vector2D acc;
	float radius;

public:
	Particle(float _radius, Vector2D _pos);

	void AddForce(Vector2D _f);
	void Draw();
	void UpdatePosition();
	Vector2D GetPosition();
	void SetPosition(Vector2D _pos);

};