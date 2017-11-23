//	cshow a simple slide show program.
//
//	Copyright (C) 2017 Streanga Sarmis-Stefan.
//
//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program, if not, see <http://www.gnu.org/licenses/>.

#include "video.h"

namespace cshow {



	video::video(SDL_Renderer* renderer, const std::string& path, const vec2& position, const vec2& size)
	: size(size), position(position), renderer(renderer), videoStream(-1){
		av_register_all();
		avformat_network_init();
		
		rect.w = size.x;
		rect.h = size.y;
		rect.x = position.x;
		rect.y = position.y;

		videoStream = -1;

		pFormatCtx = avformat_alloc_context();
		
		// Open video file
		if (avformat_open_input(&pFormatCtx, path.c_str(), NULL, NULL) != 0)
			std::cout << "Couldn't open file" << std::endl;

		// Retrieve stream information
		if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
			std::cout << "Couldn't find stream information" << std::endl;

		// Dump information about file onto standard error
		/*
		av_dump_format(pFormatCtx, 0, path.c_str(), 0);
		std::cout << std::endl;
		*/
		
		// Find the first video stream
		std::cout << pFormatCtx->nb_streams << std::endl;
		for (int i = 0; i < pFormatCtx->nb_streams; i++) {
			if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoStream = i;
				break;
			}
		}

		if (videoStream == -1)
			std::cout << "Didn't find a video stream" << std::endl;

		 // Get a pointer to the codec context for the video stream
		pCodecCtx = pFormatCtx->streams[videoStream]->codec;

		// Find the decoder for the video stream
		pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
		if (pCodec == NULL) {
			std::cout << "Codec not found" << std::endl;
		}
		// Copy context
		pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
		pCodecCtx = avcodec_alloc_context3(pCodec);

		if (avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
			std::cout << "Error copying codec context" << std::endl;
		}
		// Open codec
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
			std::cout << "Could not open codec" << std::endl;

		// Allocate video frame
		pFrame = av_frame_alloc();

		texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_YV12,
			SDL_TEXTUREACCESS_STREAMING,
			pCodecCtx->width,
			pCodecCtx->height
		);

		initBlend(texture);

		if (!texture) {
			std::cout << "SDL: could not create texture" << std::endl;
		}

		sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
			AV_PIX_FMT_YUV420P, SWS_BILINEAR, NULL, NULL, NULL);


		// set up YV12 pixel array (12 bits per pixel)
		yPlaneSz = pCodecCtx->width * pCodecCtx->height;
		uvPlaneSz = pCodecCtx->width * pCodecCtx->height / 4;
		yPlane = (uint8_t*)malloc(yPlaneSz);
		uPlane = (uint8_t*)malloc(uvPlaneSz);
		vPlane = (uint8_t*)malloc(uvPlaneSz);
		if (!yPlane || !uPlane || !vPlane)
			std::cout << "Could not allocate pixel buffers" << std::endl;

		uvPitch = pCodecCtx->width / 2;
	}

		void video::render() {
			// this should the the only one in the slide anyway because it hangs the slide...

			if (av_read_frame(pFormatCtx, &packet) >= 0) {
			
				// Is this a packet from the video stream?
				if (packet.stream_index == videoStream) {
					// Decode video frame
					avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

					// Did we get a video frame?
					if (frameFinished) {
						AVPicture pict;
						pict.data[0] = yPlane;
						pict.data[1] = uPlane;
						pict.data[2] = vPlane;
						pict.linesize[0] = pCodecCtx->width;
						pict.linesize[1] = uvPitch;
						pict.linesize[2] = uvPitch;

						// Convert the image into YUV format that SDL uses
						sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data,
							pFrame->linesize, 0, pCodecCtx->height, pict.data,
							pict.linesize);

						SDL_UpdateYUVTexture(texture, NULL, yPlane, pCodecCtx->width, uPlane,
							uvPitch, vPlane, uvPitch
						);
						
						SDL_RenderCopy(renderer, texture, NULL, &rect);
					}
				}
				av_packet_unref(&packet);
				
			}
	}

	video::~video() {
		// Free the YUV frame
		av_frame_free(&pFrame);
		free(yPlane);
		free(uPlane);
		free(vPlane);

		// Close the codec
		avcodec_close(pCodecCtx);
		avcodec_close(pCodecCtxOrig);

		// Close the video file
		avformat_close_input(&pFormatCtx);
	}


}