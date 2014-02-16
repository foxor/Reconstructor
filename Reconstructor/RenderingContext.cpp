#include "RenderingContext.h"

RenderingContext::RenderingContext(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("", 0, 0, width, height, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(displayWindow);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	scene = new Scene();
	scene->initFrustrum(width, height, pi / 8);
}

void RenderingContext::draw() {
	scene->draw();
	SDL_GL_SwapWindow(displayWindow);
}