#include "Scene.h"

Scene::Scene(GLdouble width, GLdouble height) {
	aspect = width / height;
	glGenTextures(1, sourceFrame);
	glBindTexture(GL_TEXTURE_2D, sourceFrame[0]);
}

void Scene::draw(Decoder *decoder)
{
	const GLdouble billboardDepth = -1.0;

	glTexImage2D(GL_TEXTURE_2D, 0, 3, decoder->width(), decoder->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, decoder->pFrameRGB->data[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	GLdouble right = rightClip(billboardDepth);
	GLdouble top = topClip(billboardDepth);

	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-right, top, billboardDepth);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-right, -top, billboardDepth);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(right, -top, billboardDepth);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-right, top, billboardDepth);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(right, -top, billboardDepth);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(right, top, billboardDepth);

	glEnd();
}

GLdouble Scene::rightClip(GLdouble depth) {
	return tan(FoV / 2.0) * abs(depth);
}

GLdouble Scene::topClip(GLdouble depth) {
	return rightClip(depth) * aspect;
}

void Scene::initFrustrum() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble ZNear = 0.1;
	GLdouble ZFar = 10;
	GLdouble right = rightClip(ZNear);
	GLdouble top = topClip(ZNear);
	glFrustum(-right, right, -top, top, ZNear, ZFar);

	// Safe for other code to assume we're in modelview mode
	glMatrixMode(GL_MODELVIEW);
}