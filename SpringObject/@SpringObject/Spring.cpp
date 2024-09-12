#include <stdlib.h>
#include "Spring.h"
#include "glut.h"


Spring::Spring(const float constant,const float _restLength, Particle * _end1, Particle * _end2)
	: springConstant(constant), restLength(_restLength) , end1(_end1), end2(_end2) {}

void Spring::Update() {

	Vector2D d = end1->GetPosition() - end2->GetPosition();
	float force = -springConstant * (d.GetSize() - restLength);
	Vector2D forceVector = d.GetUnitVector() * force;
	end1->AddForce(forceVector * 0.5);
	end2->AddForce(forceVector * -1 * 0.5);


	end1->UpdatePosition();
	end2->UpdatePosition();

}

void Spring::Draw() {

	end1->Draw();
	end2->Draw();
	
	glBegin(GL_LINES);
	
	glVertex2d(end1->GetPosition().GetX(), end1->GetPosition().GetY());
	glVertex2d(end2->GetPosition().GetX(), end2->GetPosition().GetY());

	glEnd();
	
	}