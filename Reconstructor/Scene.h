#ifndef SCENE
#define SCENE

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "VideoToRgb.h"

const GLdouble pi = 3.1415926535897932384626433832795;

class Scene {
private:
	GLuint sourceFrame[1];
	GLdouble FoV = pi / 4.0;
	GLdouble rightClip(GLdouble depth);
	GLdouble topClip(GLdouble depth);
	GLdouble aspect;
public:
	Scene(GLdouble width, GLdouble height);
	void draw(Decoder*);
	void initFrustrum();
};
#endif