//	cshow a simple slide show program.
//
//	Copyright (C) 2017 Streanga Sarmis-Stefan<streangasarmis@gmail.com>
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

#include "window.h"

namespace cshow {


	window::window():window(1280, 768, "cshow presentation") {}
	
	window::window(const vec3& properties):
	window(properties.z > 0 ? properties.x : 0, properties.z > 0 ? properties.y : 0, "cshow presentation"){}

	window::window(uint32_t width, uint32_t height, const char* title):width(width), height(height){
		SDL_DisplayMode current;

		if (width == 0 && height == 0) { // fullscreen
			SDL_GetCurrentDisplayMode(0, &current);

			sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				current.w, current.h, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
			
			this->width = current.w;
			this->height = current.h;

		} else { // borderless
			sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
		}
		
		if (sdlWindow == NULL) {
			std::cout << "For some reason I cannot make a window..." << std::endl;
			setRunning(false);
		} else setRunning(true);
		
		SDL_GL_CreateContext(sdlWindow);
		SDL_GL_SetSwapInterval(0);

	}

	void window::setRunning(bool running){
		this->running = running;
	}

	uint32_t window::getWidth() const {
		return width;
	}

	uint32_t window::getHeight() const {
		return height;
	}

	bool window::getRunning() const {
		return running;
	}

	SDL_Window* window::getWindow() const {
		return sdlWindow;
	}


	window::~window() {
		SDL_DestroyWindow(sdlWindow);
	}
}