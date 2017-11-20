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

#include <SDL.h>
#include <SDL_ttf.h>

#include "vec2.h"
#include "vec3.h"
#include "fadecomponent.h"
#include "staticcomponent.h"

namespace cshow {


	class textline : public fadecomponent, public staticcomponent {

		private:
			std::string			text;
			vec3				color;
			vec2				position;
			uint32_t			size;
			SDL_Texture*		Message;
			SDL_Rect			Message_rect;
			SDL_Renderer*		renderer;
			SDL_Surface*		surfaceMessage;

		public:
			textline() = default;
			textline(SDL_Renderer* renderer, const std::string& text, const vec3& background, const vec3& color, const vec2& position, uint32_t size);
			~textline();

			void clear();
			void render() override;
	};

}