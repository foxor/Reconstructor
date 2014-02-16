#include "VideoToRgb.h"

Decoder::Decoder(char* fName) {
	// Register all formats and codecs
	av_register_all();

	// Open video file
	if (avformat_open_input(&pFormatCtx, fName, NULL, NULL))
		throw FILE_NOT_FOUND;

	// Retrieve stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
		throw NO_STREAM_INFORMATION;

	// Find the first video stream
	videoStream = -1;
	for (i = 0; i < pFormatCtx->nb_streams; i++)
	if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
	{
		videoStream = i;
		break;
	}
	if (videoStream == -1)
		throw NO_STREAM_INFORMATION;

	// Get a pointer to the codec context for the video stream
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;

	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
		throw CANNOT_FIND_CODEC;

	// Inform the codec that we can handle truncated bitstreams -- i.e.,
	// bitstreams where frame boundaries can fall in the middle of packets
	if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
		pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;

	// Open codec
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
		throw CANNOT_OPEN_CODEC;

	// Allocate video frame
	pFrame = av_frame_alloc();

	// Allocate an AVFrame structure
	pFrameRGB = av_frame_alloc();
	if (pFrameRGB == NULL)
		throw CANNOT_ALLOCATE_BUFFER;

	// Determine required buffer size and allocate buffer
	numBytes = avpicture_get_size(PIX_FMT_RGB24, width(), height());
	buffer = new uint8_t[numBytes];

	// Assign appropriate parts of buffer to image planes in pFrameRGB
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, width(), height());

	// Prepare to convert YUV to RGB
	conversionCtx = sws_getContext(width(), height(), pCodecCtx->pix_fmt, width(), height(), PIX_FMT_RGB24, 0, NULL, NULL, NULL);
}

Decoder::~Decoder() {
	sws_freeContext(conversionCtx);

	// Free the RGB image
	delete[] buffer;
	av_free(pFrameRGB);

	// Free the YUV frame
	av_free(pFrame);

	// Close the codec
	avcodec_close(pCodecCtx);

	// Close the video file
	avformat_close_input(&pFormatCtx);
}

int Decoder::width() {
	return pCodecCtx->width;
}

int Decoder::height() {
	return pCodecCtx->height;
}

bool Decoder::nextFrame()
{
	static AVPacket packet;
	static int      bytesRemaining = 0;
	static bool     fFirstTime = true;
	int             bytesDecoded;
	int             frameFinished;

	// First time we're called, set packet.data to NULL to indicate it
	// doesn't have to be freed
	if (fFirstTime)
	{
		fFirstTime = false;
		packet.data = NULL;
	}

	// Decode packets until we have decoded a complete frame
	while (true)
	{
		// Work on the current packet until we have decoded all of it
		while (bytesRemaining > 0)
		{
			// Decode the next chunk of data
			bytesDecoded = avcodec_decode_video2(pCodecCtx, pFrame,
				&frameFinished, &packet);

			// Was there an error?
			if (bytesDecoded < 0)
			{
				fprintf(stderr, "Error while decoding frame\n");
				return false;
			}

			bytesRemaining -= bytesDecoded;

			// Did we finish the current frame? Then we can return
			if (frameFinished)
				return true;
		}

		// Read the next packet, skipping all packets that aren't for this
		// stream
		do
		{
			// Free old packet
			if (packet.data != NULL)
				av_free_packet(&packet);

			// Read new packet
			if (av_read_frame(pFormatCtx, &packet) < 0)
				goto loop_exit;
		} while (packet.stream_index != videoStream);

		bytesRemaining = packet.size;
	}

loop_exit:

	// Decode the rest of the last frame
	bytesDecoded = avcodec_decode_video2(pCodecCtx, pFrame,
		&frameFinished, &packet);

	// Free last packet
	if (packet.data != NULL)
		av_free_packet(&packet);

	return frameFinished != 0;
}

void Decoder::ToRGB() {
	// Translate frame to RGB in the buffer
	sws_scale(conversionCtx, pFrame->data, pFrame->linesize, 0, height(), pFrameRGB->data, pFrameRGB->linesize);
}