#include "Particle.h"
#include "glut.h"

#define PI		3.141592

Particle::Particle(Vector _Pos, float _radius, float _mass) :
	Pos(_Pos), oldPos(_Pos), radius(_radius), mass(_mass), acc(Vector())
{}

void Particle::AddForce(Vector force) {

	acc += force / mass;

}
void Particle::Draw() {


	glBegin(GL_LINES);

	for (int i = 0; i < 360; i++) {
		float radian = 2 * PI * (float)i / 360;
		float _x = radius * cos(radian), _y = radius * sin(radian);
		glVertex3f(Pos.x + _x, Pos.y + _y, Pos.z);
	}

	glEnd();
}
void Particle::Update() {

	Vector temp = Pos;
	Pos = Pos + (Pos - oldPos) * 0.9f + acc * 0.5 * 0.5;
	acc = Vector();
	oldPos = temp;

} 