#include <stdio.h>
#include "glut.h"

#include "Particle.h"
#include "Spring.h"

Particle p1(5.f, Vector2D(10.f, 10.f));
Particle p2(5.f, Vector2D(-10.f, -10.f));
Spring spring(0.01f, 10.f, &p1, &p2);

void glReshape(int w, int h);
void glDisplay();
void Update();
void Mouse(int button, int state, int x, int y);

void main() {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Spring 2D");
	glutReshapeFunc(glReshape);
	glutDisplayFunc(glDisplay);
	glutIdleFunc(Update);
	glutMouseFunc(Mouse);
	glutMainLoop();

}

void glReshape(int w, int h) {
	glLoadIdentity();						// 단위행렬
	glViewport(0, 0, w, h);					// 뷰포트 지정 (윈도우에 그릴 영역)
	gluOrtho2D(-100.f, 100.f, -100.f, 100.f);		// 좌표계 재지정, X : 0 ~ 100, Y : 0 ~ 100
}

void glDisplay() {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	p1.Draw();
	spring.Draw();

	glFlush();

}

void Mouse(int button, int state, int x, int y) {
	
	switch (button) {
	case GLUT_LEFT_BUTTON:
		float cvt_x, cvt_y;
		cvt_x = (x - 700 / 2) / (float)700 * 2 * 100,
		cvt_y = -((y - 700 / 2) / (float)700 * 2) * 100;
		//printf("cvt_x cvt_y : %f %f\n", cvt_x, cvt_y);
		p1.SetPosition(Vector2D(cvt_x, cvt_y));
		break;	
	}
}

void Update() {
	//cvt_x = (x - width / 2) / (float)width * 2 * MAX,
	//cvt_y = -((y - height / 2) / (float)height * 2) * MAX;
	//p.UpdatePosition();
	spring.Update();
	glutPostRedisplay();
}