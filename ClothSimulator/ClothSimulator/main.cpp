#include <stdio.h>
#include <stdlib.h>
#include "Cloth.h"
#include "glut.h"


float _zoom = 15.0f;
float _rotate_x = 0.0f;
float _rotate_y = 0.001f;
float _translate_x = 0.0f;
float _translate_y = 0.0f;
int last_x = 0;
int last_y = 0;

unsigned char _btnState[3] = { 0, };

//Particle P(Vector(), 1.f, 1);

Cloth cloth(Vector(), -0.05f , 30, 30);

void init() {
	// ���̰� ��� ����
	glEnable(GL_DEPTH_TEST);
	//P.AddForce(Vector(0.00001, 0, 0));
}


void display() {
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// ��������� �ҷ���, (��� ������ �ʱⰪ)
	glTranslatef(0.0f, 0.0f, -_zoom);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glRotatef(_rotate_x, 1, 0, 0);
	glRotatef(_rotate_y, 0, 1, 0);

	//P.Draw();	
	cloth.Draw();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glutSwapBuffers();
	// ���� ���۸�

}

void reshape(int w, int h) {
	if (w == 0)
		h = 1;

	glViewport(0, 0, w, h);	// �׷��� ����ġ���� ������
	glMatrixMode(GL_PROJECTION);
	// ���� ����� �Ǵ� ��� ���� (ī�޶� ��ǥ ���)
	glLoadIdentity();
	// �ʱ�ȭ
	gluPerspective(90.0f, (float)w / h, 0.01f, 100.0f);
	// Perspective ��� ����, 90���� fov, ��Ⱦ��, near, far�� (ī�޶� ��ġ)

	glMatrixMode(GL_MODELVIEW);
	// ���� ����� �Ǵ� ��� ���� (���� ��ǥ ����� ���� ������� ����.)	

	// OpenGL�� �⺻ ����
}

void mouseMotion(int x, int y) {

	int diff_x = x - last_x;
	int diff_y = y - last_y;
	// ���콺�� �巡�� �� �� �Ÿ��� ���

	if (_btnState[2]) {
		_zoom -= (float)0.05f * diff_x;
	}
	else if (_btnState[0]) {
		_rotate_x += (float)0.05f * diff_y;
		_rotate_y += (float)0.05f * diff_x;
	}
	else if (_btnState[1]) {
		_translate_x += (float)0.005f * diff_x;
		_translate_y -= (float)0.005f * diff_y;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
	last_x = x;
	last_y = y;
	// ���콺�� Ŭ���� �� ������ ��ǥ

	switch (button) {
	case GLUT_LEFT_BUTTON:
		printf("left button\n");
		_btnState[0] = ((GLUT_DOWN == state) ? 1 : 0);
		break;
	case GLUT_MIDDLE_BUTTON:
		printf("middle button\n");
		_btnState[1] = ((GLUT_DOWN == state) ? 1 : 0);
		break;
	case GLUT_RIGHT_BUTTON:
		printf("right button\n");
		_btnState[2] = ((GLUT_DOWN == state) ? 1 : 0);
		break;
	}

	glutPostRedisplay();
	// ����� _zoom ���� _translate�� ��ǥ������ Redisplay ����
}


void keyboard(unsigned char key, int x, int y) {

	cloth.MoveAnchor(key);
	glutPostRedisplay();

}

void Update() {

	//P.Update();
	cloth.Update();
	glutPostRedisplay();
}

void main() {

	printf("press w to make anchors move front\n");
	printf("press s to make anchors move back\n");
	printf("press a to make anchors move left between anchors\n");
	printf("press d to make anchors move right between anchors\n");
	printf("press q to make anchors move narrow between anchors\n");
	printf("press e to make anchors move wide between anchors\n");



	glutInitWindowSize(640, 480);			// â ũ��
	glutInitWindowPosition(100, 100);		// â ù ��ġ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Cloth Simulator");
	glutDisplayFunc(display);				// display callback �Լ�
	glutReshapeFunc(reshape);				// reshape callback �Լ� // �ּ�ȭ�� �ִ�ȭ �� â�� ���°� ����� ��� �ٽ� �׸� 
	glutMouseFunc(Mouse);					// ���콺 �ݹ� �Լ�
	glutMotionFunc(mouseMotion);			// ���콺 ���(�巡��) �ݹ� �Լ�
	glutKeyboardFunc(keyboard);
	glutIdleFunc(Update);
	init();									// ���� Ŭ����, ���� �ʱ�ȭ
	glutMainLoop();
}

