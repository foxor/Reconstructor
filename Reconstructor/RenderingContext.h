#ifndef RENDERINGCONTEXT
#define RENDERINGCONTEXT

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Scene.h"

class RenderingContext {
private:
	SDL_Window* displayWindow;
	Scene* scene;

public:
	RenderingContext(int, int);
	void draw(Decoder*);
};
#endif