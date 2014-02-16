extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

#include <stdio.h>

const int FILE_NOT_FOUND = 1;
const int NO_STREAM_INFORMATION = 2;
const int CANNOT_FIND_CODEC = 3;
const int CANNOT_OPEN_CODEC = 4;
const int CANNOT_ALLOCATE_BUFFER = 5;

class Decoder {
protected:
	AVFormatContext *pFormatCtx = NULL;
	unsigned int    i;
	int				videoStream;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFrame         *pFrame;
	AVFrame         *pFrameRGB;
	int             numBytes;
	SwsContext		*conversionCtx;

public:
	uint8_t *buffer;
	Decoder(char* fName);
	~Decoder();
	int width();
	int height();
	bool nextFrame();
};