#include "GlSetup.h"

const GLdouble pi = 3.1415926535897932384626433832795;
SDL_Window* displayWindow;

void Display_Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	SDL_GL_SwapWindow(displayWindow);
}

void initFrustrum(GLdouble width, GLdouble height, GLdouble halfFOV) {
	GLdouble ratio = width / height;
	GLdouble ZNear = 0.1;
	GLdouble ZFar = 10;
	GLdouble rightClip = tan(halfFOV) * ZNear;
	GLdouble topClip = rightClip * ratio;
	glFrustum(-rightClip, rightClip, -topClip, topClip, ZNear, ZFar);
}

int initGL(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("", 0, 0, width, height, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(displayWindow);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	initFrustrum(width, height, pi / 8);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Display_Render();


	SDL_Delay(5000);
	SDL_Quit();

	return 0;
}