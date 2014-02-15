#include "GlSetup.h"

const GLdouble pi = 3.1415926535897932384626433832795;
SDL_Window* displayWindow;
SDL_Renderer* displayRenderer;

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

	SDL_RenderPresent(displayRenderer);

	SDL_GL_SwapWindow(displayWindow);
}


int initGL(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_RendererInfo displayRendererInfo;
	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &displayWindow, &displayRenderer);
	SDL_GL_CreateContext(displayWindow);
	SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
	if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
		(displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		return -1;
	}

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat ratio;
	if (height == 0) {
		height = 1;
	}

	ratio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble ZNear = 0.1;
	GLdouble ZFar = 100;
	//45 degrees = pi / 4.  Since we need left and right from 0, half that
	GLdouble halfFOV = pi / 8;
	GLdouble rightClip = tan(halfFOV) * ZNear;
	GLdouble topClip = rightClip * ratio;
	glFrustum(-rightClip, rightClip, -topClip, topClip, ZNear, ZFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Display_Render();


	SDL_Delay(5000);
	SDL_Quit();

	return 0;
}