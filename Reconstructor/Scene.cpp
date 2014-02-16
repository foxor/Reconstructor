#include "Scene.h"

Scene::Scene() {
	glGenTextures(1, sourceFrame);
	glBindTexture(GL_TEXTURE_2D, sourceFrame[0]);
}

void Scene::draw(Decoder *decoder)
{
	glTexImage2D(GL_TEXTURE_2D, 0, 3, decoder->width(), decoder->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, decoder->pFrameRGB->data[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
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