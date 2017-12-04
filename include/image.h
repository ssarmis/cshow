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

#pragma once

#include <SDL.h>
#include <SDL_Image.h>
#include <string>

#include "vec2.h"
#include "fadecomponent.h"
#include "staticcomponent.h"

namespace cshow {

	class image : public fadecomponent, public staticcomponent {

		private:
			SDL_Renderer*	renderer;
			SDL_Texture*	texture;
			SDL_Rect		destination;
			vec2			position;
			vec2			size;

		public:

			image() = default;
			image(SDL_Renderer* renderer, const std::string& path, const vec2& position, const vec2& size);
			~image();

			inline SDL_Texture* getTexture() { return texture; }
			void clear();
			void render() override;
	};


}