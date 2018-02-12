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

#include "rectangle.h"

namespace cshow {


	rectangle::rectangle(SDL_Renderer* renderer, const vec2& position, const vec3& background, const vec2& size)
		:renderer(renderer), position(position), size(size) {


		destination.x = position.x;
		destination.y = position.y;
		destination.w = size.x;
		destination.h = size.y;

		SDL_Surface* rect;
		rect = SDL_CreateRGBSurface(0, size.x, size.y, 32, 0, 0, 0, 0);
		SDL_FillRect(rect, NULL, SDL_MapRGB(rect->format, background.x, background.y, background.z));

		texture = SDL_CreateTextureFromSurface(renderer, rect);
		SDL_FreeSurface(rect);

		initBlend(texture);
	}

	void rectangle::render() {
		SDL_RenderCopy(renderer, texture, NULL, &destination);
	}

	rectangle::~rectangle() {
		SDL_DestroyTexture(texture);
	}


}