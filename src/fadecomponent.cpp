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

#include "fadecomponent.h"

namespace cshow {

	void fadecomponent::initBlend(SDL_Texture* texture) {
		this->texture = texture;
		alpha = 255;
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}

	void fadecomponent::setMaxAlpha() {
		alpha = 255;
		SDL_SetTextureAlphaMod(texture, alpha);
	}

	void fadecomponent::setMinAlpha() {
		alpha = 0;
		SDL_SetTextureAlphaMod(texture, alpha);
	}

	void fadecomponent::fadeIn() {
		if (alpha < 255) {
			alpha++;
			SDL_SetTextureAlphaMod(texture, alpha);
		}
	}
	
	void fadecomponent::fadeOut() {
		if (alpha > 0) {
			alpha--;
			SDL_SetTextureAlphaMod(texture, alpha);
		}
	}

}