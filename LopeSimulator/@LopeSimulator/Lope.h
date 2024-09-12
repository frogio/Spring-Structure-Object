#pragma once

#include <vector>
#include "Particle.h"

using namespace std;

class Lope {
private:
	int length;
	int thickness;
	int restLength;
	bool activateGravity;
	vector<Particle *> particles;

public:
	Lope(int _length, int _thickness, bool _activateGravity);
	void Draw();
	void Update();
	void SetHeadPosition(Vector2D _pos);
	void SetGravity(bool _gravity);
	Particle* GetParticle(float x, float y);
};