#include "VideoToRgb.h"
#include "GlSetup.h"

int main(int argc, char **argv){
	decode_mpeg("C:\\Users\\Isaac\\Code\\Reconstructor\\Debug\\testVid.mp4");
	initGL(800, 600);

	return 0;
}