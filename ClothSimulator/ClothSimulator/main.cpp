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
	// 깊이값 사용 여부
	glEnable(GL_DEPTH_TEST);
	//P.AddForce(Vector(0.00001, 0, 0));
}


void display() {
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// 단위행렬을 불러옴, (행렬 연산의 초기값)
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
	// 더블 버퍼링

}

void reshape(int w, int h) {
	if (w == 0)
		h = 1;

	glViewport(0, 0, w, h);	// 그려질 스케치북의 사이즈
	glMatrixMode(GL_PROJECTION);
	// 연산 대상이 되는 행렬 선택 (카메라 좌표 행렬)
	glLoadIdentity();
	// 초기화
	gluPerspective(90.0f, (float)w / h, 0.01f, 100.0f);
	// Perspective 행렬 연산, 90도의 fov, 종횡비, near, far값 (카메라 위치)

	glMatrixMode(GL_MODELVIEW);
	// 연산 대상이 되는 행렬 선택 (모델의 좌표 행렬을 연산 대상으로 삼음.)	

	// OpenGL의 기본 설정
}

void mouseMotion(int x, int y) {

	int diff_x = x - last_x;
	int diff_y = y - last_y;
	// 마우스를 드래그 할 때 거리값 계산

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
	// 마우스를 클릭할 때 최초의 좌표

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
	// 변경된 _zoom 값과 _translate된 좌표값으로 Redisplay 실행
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



	glutInitWindowSize(640, 480);			// 창 크기
	glutInitWindowPosition(100, 100);		// 창 첫 위치
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Cloth Simulator");
	glutDisplayFunc(display);				// display callback 함수
	glutReshapeFunc(reshape);				// reshape callback 함수 // 최소화나 최대화 등 창의 상태가 변경될 경우 다시 그림 
	glutMouseFunc(Mouse);					// 마우스 콜백 함수
	glutMotionFunc(mouseMotion);			// 마우스 모션(드래그) 콜백 함수
	glutKeyboardFunc(keyboard);
	glutIdleFunc(Update);
	init();									// 각종 클래스, 변수 초기화
	glutMainLoop();
}

