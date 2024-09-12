#include "Cloth.h"
#include "Particle.h"
#include "glut.h"

ClothParticle::ClothParticle(Vector _pos, float _radius, float _mass) :
	Particle(_pos, _radius, _mass) {}

void ClothParticle::Update(float springConstants) {
	
	float _2square_root = sqrt(2);

	// structure Spring Constraints
	for (int i = 0; i < structureParticle.size(); i++) {
		Particle  * p = structureParticle[i];
		Vector dist = Pos - *p->GetPos();
		Vector force = dist.GetUnitVector() * (0.2 - dist.GetSize()) * springConstants;		// k * delt_l * normalize vector
		
		p->AddForce(force * 0.5);
	}

	// shear Spring Constraints
	for (int i = 0; i < shearParticle.size(); i++) {
		Particle* p = shearParticle[i];
		Vector dist = Pos - *p->GetPos();
		Vector force = dist.GetUnitVector() * (_2square_root * 0.2 - dist.GetSize()) * springConstants;		// k * delt_l * normalize vector
		
		p->AddForce(force * 0.5);
	}
	
	// bending Spring Constraints
	for (int i = 0; i < bendingParticle.size(); i++) {
		Particle* p = bendingParticle[i];
		Vector dist = Pos - *p->GetPos();
		Vector force = dist.GetUnitVector() * (2 * 0.2 - dist.GetSize()) * springConstants;		// k * delt_l * normalize vector
		
		p->AddForce(force * 0.5);
	}
	
	// diagonal bending Spring Constraints
	for (int i = 0; i < diagonalBendingParticle.size(); i++) {
		Particle* p = diagonalBendingParticle[i];
		Vector dist = Pos - *p->GetPos();
		Vector force = dist.GetUnitVector() * (2 * _2square_root * 0.2 - dist.GetSize()) * springConstants;		// k * delt_l * normalize vector

		p->AddForce(force * 0.5);
	}
	
}

Cloth::Cloth(Vector _Pos, const float _springConstant, int _width, int _height) :
	Pos(_Pos),
	springConstant(_springConstant),
	width(_width),
	height(_height) {


	for (int y = 0; y < height; y++) {

		for (int x = 0; x < width; x++) {
			Vector pos((float)x / 5 - width / 10, (float)y / 5 - height / 10, 0);
			// 0.1, 0.1
			ClothParticle* p = new ClothParticle(pos, 0.01f, 1);
			particles.push_back(p);
		}

	}
	// 파티클 생성
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			ClothParticle* p = particles[width * y + x];
			buildAdjacency(p, x, y);
		}
	}
	// 인접정보 생성


	// Cloth Anchor
	for (int y = height - 1; y >= height - 5; y--)
		for (int x = 0; x < 5; x++)
			anchorParticleLeft.push_back(particles[width * y + x]);

	for (int y = height - 1; y >= height - 5; y--)
		for (int x = width - 1; x >= width - 5; x--)
			anchorParticleRight.push_back(particles[width * y + x]);



}

void Cloth::buildAdjacency(ClothParticle* p, int x, int y) {
	
	if (x - 1 >= 0)
		p->structureParticle.push_back(particles[width * y + (x - 1)]);

	if (x + 1 < width)
		p->structureParticle.push_back(particles[width * y + (x + 1)]);

	if (y - 1 >= 0)
		p->structureParticle.push_back(particles[width * (y - 1) + x]);

	if (y + 1 < height)
		p->structureParticle.push_back(particles[width * (y + 1) + x]);
	// structure Spring

	if (x + 1 < width && y + 1 < height)
		p->shearParticle.push_back(particles[width * (y + 1) + (x + 1)]);

	if (x + 1 < width && y - 1 >= 0)
		p->shearParticle.push_back(particles[width * (y - 1) + (x + 1)]);

	if (x - 1 >= 0 && y + 1 < height)
		p->shearParticle.push_back(particles[width * (y + 1) + (x - 1)]);

	if (x - 1 >= 0 && y - 1 >= 0 )
		p->shearParticle.push_back(particles[width * (y - 1) + (x - 1)]);
	// shear Spring

	if (x + 2 < width)
		p->bendingParticle.push_back(particles[width * y + (x + 2)]);

	if (x + 2 < width && y + 2 < height)
		p->diagonalBendingParticle.push_back(particles[width * (y + 2) + (x + 2)]);

	if (y + 2 < height)
		p->bendingParticle.push_back(particles[width * (y + 2) + x]);

	if (x - 2 >= 0 && y + 2 < height)
		p->diagonalBendingParticle.push_back(particles[width * (y + 2) + (x - 2)]);

	if (x - 2 >= 0)
		p->bendingParticle.push_back(particles[width * y + (x - 2)]);

	if (x - 2 >= 0 && y - 2 >= 0)
		p->diagonalBendingParticle.push_back(particles[width * (y - 2) + (x - 2)]);

	if (y - 2 >= 0)
		p->bendingParticle.push_back(particles[width * (y - 2) + x]);
	
	if (y - 2 >= 0 && x + 2 < width)
		p->diagonalBendingParticle.push_back(particles[width * (y - 2) + (x + 2)]);
	// bending Spring

}

void Cloth::Draw() {
	/*
	glBegin(GL_POINTS);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Vector* v = particles[width * y + x]->GetPos();
			glVertex3f(v->x, v->y, v->z);
		}

	}

	glEnd();
	*/
	glBegin(GL_TRIANGLES);

	for (int y = 0; y < height - 1; y++) {
		for (int x = 0; x < width - 1; x++) {
			Vector* v1 = particles[width * y + x]->GetPos();
			Vector* v2 = particles[width * y + (x + 1)]->GetPos();
			Vector* v3 = particles[width * (y + 1) + (x + 1)]->GetPos();
			Vector* v4 = particles[width * (y + 1) + x]->GetPos();

			Vector v_1_2 = *v1 - *v2;
			Vector v_2_3 = *v2 - *v3;
			Vector normal = v_1_2.Cross(v_2_3).GetUnitVector();
			glNormal3f(normal.x, normal.y, normal.z);

			glVertex3f(v1->x, v1->y, v1->z);
			glVertex3f(v2->x, v2->y, v2->z);
			glVertex3f(v3->x, v3->y, v3->z);

			Vector v_1_4 = *v1 - *v4;
			Vector v_4_3 = *v4 - *v3;
			normal = v_4_3.Cross(v_1_4).GetUnitVector();
			glNormal3f(normal.x, normal.y, normal.z);

			glVertex3f(v1->x, v1->y, v1->z);
			glVertex3f(v4->x, v4->y, v4->z);
			glVertex3f(v3->x, v3->y, v3->z);

		}

	}

	glEnd();

}

void Cloth::Update() {


	for (int p = 0; p < particles.size(); p++) {
		particles[p]->AddForce(Vector(0, -0.0005f, 0));		   // 아닐 경우 중력 적용


		particles[p]->Update(springConstant);
		
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++)
				if (anchorParticleLeft[5 * y + x] == particles[p]) // 앵커 파티클일 경우
					particles[p]->CancelForce();
		}
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++)
				if (anchorParticleRight[5 * y + x] == particles[p]) // 앵커 파티클일 경우
					particles[p]->CancelForce();
		}

		
		particles[p]->Particle::Update();

	}
	// 중력 작용
	
	for (int y = height - 1; y >= height - 5; y--)
		for (int x = 0; x < 5; x++)
			particles[width * y + x]->SetPos(*anchorParticleLeft[5 * (width - 1 - y) + x]->GetPos());

	for (int y = height - 1; y >= height - 5; y--)
		for (int x = width - 1; x >= width - 5; x--)
			particles[width * y + x]->SetPos(*anchorParticleRight[5 * (width - 1 - y) + (width - 1 - x)]->GetPos());
	

}

void Cloth::MoveAnchor(char dir) {

	const float moveVelocity = 0.5f;

	switch (dir) {

	case 'w':				// 앵커 앞으로
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleLeft[5 * y + x]->SetPos(*anchorParticleLeft[5 * y + x]->GetPos() + Vector(0, 0, -moveVelocity));

		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleRight[5 * y + x]->SetPos(*anchorParticleRight[5 * y + x]->GetPos() + Vector(0, 0, -moveVelocity));
		break;

	case 's':				// 앵커 뒤로
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleLeft[5 * y + x]->SetPos(*anchorParticleLeft[5 * y + x]->GetPos() + Vector(0, 0, moveVelocity));

		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleRight[5 * y + x]->SetPos(*anchorParticleRight[5 * y + x]->GetPos() + Vector(0, 0, moveVelocity));
		break;

	case 'a':				// 앵커 왼쪽
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleLeft[5 * y + x]->SetPos(*anchorParticleLeft[5 * y + x]->GetPos() + Vector(-moveVelocity, 0, 0));

		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleRight[5 * y + x]->SetPos(*anchorParticleRight[5 * y + x]->GetPos() + Vector(-moveVelocity, 0, 0));
		break;

	case 'd':				// 앵커 오른쪽
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleLeft[5 * y + x]->SetPos(*anchorParticleLeft[5 * y + x]->GetPos() + Vector(moveVelocity, 0, 0));

		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleRight[5 * y + x]->SetPos(*anchorParticleRight[5 * y + x]->GetPos() + Vector(moveVelocity, 0, 0));
		break;

	case 'q':
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleLeft[5 * y + x]->SetPos(*anchorParticleLeft[5 * y + x]->GetPos() + Vector(moveVelocity, 0, 0));

		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleRight[5 * y + x]->SetPos(*anchorParticleRight[5 * y + x]->GetPos() + Vector(-moveVelocity, 0, 0));
		break;
	case 'e':
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleLeft[5 * y + x]->SetPos(*anchorParticleLeft[5 * y + x]->GetPos() + Vector(-moveVelocity, 0, 0));

		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
				anchorParticleRight[5 * y + x]->SetPos(*anchorParticleRight[5 * y + x]->GetPos() + Vector(moveVelocity, 0, 0));
		break;

	}

}