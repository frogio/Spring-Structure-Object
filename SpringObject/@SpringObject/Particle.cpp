#include "Particle.h"
#include "glut.h"

Particle::Particle(float _radius, Vector2D _pos) 
	: radius(_radius), position(_pos), old_position(_pos), mass(1), acc(Vector2D()){}

void Particle::AddForce(Vector2D _f) {

	acc = _f * (1.f / mass);

}
void Particle::Draw() {

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i++) {
		float radian = 2 * PI * (float)i / 360;
		float x = position.x + radius * cos(radian), y = position.y + radius * sin(radian);

		glVertex2d(x, y);

	}

	glEnd();

}
void Particle::UpdatePosition() {
	// Verlet Intergration�� Ȱ���� ��ġ ������Ʈ
	// ������ ��� ����.
	Vector2D tmp = position;
	position = position + (position - old_position) + acc;
	old_position = position;

}

Vector2D Particle::GetPosition() {
	return position;
}

void Particle::SetPosition(Vector2D _pos) {
	position = _pos;
	old_position = _pos;
}