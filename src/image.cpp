//  cshow a simple slide show program.
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

#include "image.h"

namespace cshow {

	image::image(SDL_Renderer* renderer, const std::string& path, const vec2& position, const vec2& size)
	:renderer(renderer), position(position), size(size) {
		texture = IMG_LoadTexture(renderer, path.c_str());

		initBlend(texture);

		destination.x = position.x;
		destination.y = position.y;
		destination.w = size.x;
		destination.h = size.y;
	}

	void image::render() {
		SDL_RenderCopy(renderer, texture, NULL, &destination);
	}

	void image::clear(){
		SDL_DestroyTexture(texture);
	}

}