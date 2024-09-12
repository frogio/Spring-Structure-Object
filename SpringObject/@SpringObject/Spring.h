#pragma once
#include "Particle.h"

class Spring {
private:
	Particle * end1;
	Particle * end2;
	const float springConstant;
	const float restLength;

public:

	Spring(const float constant,const float _restLength , Particle * _end1, Particle * _end2);
	void Update();
	void Draw();

};