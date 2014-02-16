#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

const GLdouble pi = 3.1415926535897932384626433832795;

class Scene {
public:
	Scene();
	void draw();
	void initFrustrum(GLdouble width, GLdouble height, GLdouble halfFOV);
};