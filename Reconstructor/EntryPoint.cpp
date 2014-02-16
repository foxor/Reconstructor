#include "VideoToRgb.h"
#include "GlSetup.h"

int main(int argc, char **argv){
	Decoder* d = new Decoder("C:\\Users\\Isaac\\Code\\Reconstructor\\Debug\\testVid.mp4");
	initGL(d->width(), d->height());
	while (d->nextFrame());

	return 0;
}