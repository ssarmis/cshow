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

#include "textline.h"

namespace cshow {

	textline::textline(SDL_Renderer* renderer, const std::string& text, const vec3& background, const vec3& color, const vec2& position, uint32_t size)
		:text(text), color(color), position(position), size(size), renderer(renderer) {
		
		TTF_Font* Sans = TTF_OpenFont("fonts/Sansation-Bold.ttf", size);
		
		//TTF_SetFontOutline(Sans, 2);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

		TTF_SetFontHinting(Sans, TTF_HINTING_NORMAL);

		if (background.x != -1 && background.y != -1 && background.z != -1) {
			surfaceMessage = TTF_RenderUTF8_Shaded(Sans, text.c_str(), { static_cast<uint8_t>(color.x), static_cast<uint8_t>(color.y), static_cast<uint8_t>(color.z), 255 },
			{ static_cast<uint8_t>(background.x), static_cast<uint8_t>(background.y), static_cast<uint8_t>(background.z), 255 });
		} else {
			surfaceMessage = TTF_RenderUTF8_Blended(Sans, text.c_str(),
			{ static_cast<uint8_t>(color.x), static_cast<uint8_t>(color.y), static_cast<uint8_t>(color.z), 255 });
		}

		if (!surfaceMessage) {
			std::cout << "Oh My Goodness, an error : " << TTF_GetError() << std::endl;
		}
		
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		initBlend(Message);
		
		Message_rect.x = position.x;
		Message_rect.y = position.y;
		Message_rect.w = surfaceMessage->w;
		Message_rect.h = surfaceMessage->h;
	}

	void textline::render() {
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	}

	textline::~textline() {
		SDL_FreeSurface(surfaceMessage);
	}

}