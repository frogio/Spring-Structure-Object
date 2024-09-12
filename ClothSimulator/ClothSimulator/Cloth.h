#pragma once
#include <vector>
#include <math.h>
#include "Particle.h"


class ClothParticle : public Particle {

public:
	ClothParticle(Vector _pos, float _radius, float _mass);
	std::vector<Particle*> structureParticle;
	std::vector<Particle*> shearParticle;
	std::vector<Particle*> bendingParticle;
	std::vector<Particle*> diagonalBendingParticle;

	void Update(float springConstants);
	void CancelForce() { acc = Vector(); }
};

class Cloth {
	Vector Pos;
	int width, height;
	const float springConstant;
	std::vector<ClothParticle *> particles;
	std::vector<ClothParticle *> anchorParticleLeft;
	std::vector<ClothParticle *> anchorParticleRight;
	void buildAdjacency(ClothParticle* p, int x, int y);
public:
	Cloth(Vector _Pos, const float _springConstant, int _width, int _height);
	void Update();
	void Draw();
	void MoveAnchor(char dir);

};