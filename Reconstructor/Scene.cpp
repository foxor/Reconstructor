#include "Scene.h"

Scene::Scene() {
}

void Scene::draw()
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
}

void Scene::initFrustrum(GLdouble width, GLdouble height, GLdouble halfFOV) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble aspect = width / height;
	GLdouble ZNear = 0.1;
	GLdouble ZFar = 10;
	GLdouble rightClip = tan(halfFOV) * ZNear;
	GLdouble topClip = rightClip * aspect;
	glFrustum(-rightClip, rightClip, -topClip, topClip, ZNear, ZFar);

	// Safe for other code to assume we're in modelview mode
	glMatrixMode(GL_MODELVIEW);
}