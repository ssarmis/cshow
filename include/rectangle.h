//	cshow a simple slide show program.
//
//	Copyright (C) 2018 Streanga Sarmis-Stefan<streangasarmis@gmail.com>
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

#include "vec2.h"
#include "vec3.h"
#include "fadecomponent.h"
#include "staticcomponent.h"

namespace cshow {

	class rectangle : public fadecomponent, public staticcomponent {

	private:
		SDL_Renderer*		renderer;
		SDL_Texture*		texture;
		SDL_Surface*		rect;
		SDL_Rect			destination;
		vec2				position;
		vec2				size;

	public:

		rectangle() = default;
		rectangle(SDL_Renderer* renderer, const vec2& position, const vec3& background, const vec2& size);
		~rectangle();

		inline SDL_Texture* getTexture() { return texture; }
		void clear();
		void render() override;

	};

}
