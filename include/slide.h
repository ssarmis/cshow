//	cshow a simple slide show program.
//
//	Copyright (C) 2017 Stephancode(Streanga Sarmis-Stefan).
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

#pragma once

#include <list>
#include <SDL.h>
#include <string>
#include <iostream>
#include <iterator>

#include "vec2.h"
#include "vec3.h"
#include "textline.h"
#include "image.h"
#include "video.h"
#include "rectangle.h"
#include "dynamiccomponent.h"
#include "staticcomponent.h"


namespace cshow {

	class slidemanager;

	class slide {

		private:
			static bool 			canRefresh;
			uint32_t				width;
			uint32_t				height;
			vec3					backgroundColor;
			SDL_Renderer*			renderer;
			SDL_Surface*			bgrect;
			SDL_Texture*			bgtxt;
			SDL_Rect				bg;

		public:
			std::list<dynamiccomponent*> dynamicComponents;
			std::list<staticcomponent*> staticComponents;
			
			/*
			std::vector<textline>	textLines;
			std::vector<image>		images;
			std::vector<rectangle>	rects;
			std::vector<video>		videos;
			*/

			slide();
			slide(SDL_Renderer* renderer, uint32_t width, uint32_t height);
			
			void eventHandling(const SDL_Event& event);

			void setBackground(const vec3& color);

			void initSelect();

			void render(SDL_Renderer* renderer);
			void renderStaticComponents(SDL_Renderer* renderer);
			void renderDynamicComponents(SDL_Renderer* renderer);

			void clearScreen(SDL_Renderer* renderer);
			void clear();

			void noRefresh();
	};

}