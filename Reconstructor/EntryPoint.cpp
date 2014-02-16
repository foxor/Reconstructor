#include "VideoToRgb.h"
#include "RenderingContext.h"

int main(int argc, char **argv){
	Decoder* d = new Decoder("C:\\Users\\Isaac\\Code\\Reconstructor\\Debug\\testVid.mp4");
	RenderingContext* r = new RenderingContext(d->width(), d->height());
	while (d->nextFrame()) {
		d->ToRGB();
		r->draw(d);
	}
	SDL_Quit();
	return 0;
}