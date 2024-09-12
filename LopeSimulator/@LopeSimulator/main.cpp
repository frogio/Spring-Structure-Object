#include <stdio.h>
#include <stdlib.h>
#include "glut.h"

#include "Lope.h"

void glReshape(int w, int h);
void glDisplay();
void Update();
void mouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

bool activateGravity = true;
Lope lope(50, 6, activateGravity);


void main() {

	printf("Press g button to switch gravity activation\n");

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Lope 2D");
	glutReshapeFunc(glReshape);
	glutDisplayFunc(glDisplay);
	glutIdleFunc(Update);
	glutMouseFunc(Mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
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

	lope.Draw();
	
	glFlush();

}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'g' || key == 'G') {
		activateGravity = !activateGravity;
		lope.SetGravity(activateGravity);
		if (activateGravity)
			printf("gravity activate\n");
		else
			printf("gravity inactivate\n");

	}

}

int lastx, lasty;
Vector2D cursorVector;
Particle * selectedParticle = NULL;

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		
		float cvt_x, cvt_y;

		cvt_x = (x - 700 / 2) / (float)700 * 2 * 100,
		cvt_y = -((y - 700 / 2) / (float)700 * 2) * 100;

		selectedParticle = lope.GetParticle(cvt_x, cvt_y);

	}
}


void mouseMotion(int x, int y) {

	if(activateGravity == false){

		float cvt_x, cvt_y;
		cvt_x = (x - 700 / 2) / (float)700 * 2 * 100,
		cvt_y = -((y - 700 / 2) / (float)700 * 2) * 100;
		//cursorVector = Vector2D(cvt_x - cvt_lastx, cvt_y - cvt_lasty);
		
		if(selectedParticle != NULL){
			selectedParticle->SetPosition(Vector2D(cvt_x, cvt_y));
		}
	}
}

int offset = 1;
float headX = 90.f, headY = 90.f;

void Update() {

	lope.Update();
	
	if(activateGravity){

		lope.SetHeadPosition(Vector2D(headX, headY));

		if (headX == 90.f || headX == -90.f)
			offset *= -1;
			
		headX += offset;

	}
	glutPostRedisplay();
}