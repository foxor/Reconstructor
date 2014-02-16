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
public:
	Scene();
	void draw(Decoder*);
	void initFrustrum(GLdouble width, GLdouble height, GLdouble halfFOV);
};
#endif