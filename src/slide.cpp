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

#include "slide.h"

namespace cshow {

	bool slide::canRefresh = true;

	slide::slide() {}

	slide::slide(SDL_Renderer* renderer, Uint32 width, Uint32 height):width(width), height(height),
	backgroundColor(vec3()), renderer(renderer) {}

	void slide::eventHandling(const SDL_Event& event) {
		switch (event.type) {
			case SDL_KEYDOWN:
				//if (event.key.keysym.sym == SDLK_RIGHT) slidemanager::nextSlide();
				break;

			default:
				break;
		}
	}

	void slide::render(SDL_Renderer* renderer){
		if(canRefresh){
			clearScreen(renderer);
			noRefresh();
			renderComponents(renderer);
		}
		for (Uint32 i = 0; i < videos.size(); i++) videos[i].render();
	}

	void slide::setBackground(const vec3& color) {
		backgroundColor = color;
	}


	void slide::clear() {
		for (Uint32 i = 0; i < images.size(); i++) images[i].clear();
		for (Uint32 i = 0; i < textLines.size(); i++) textLines[i].clear();
		for (Uint32 i = 0; i < rects.size(); i++) rects[i].clear();
		for (Uint32 i = 0; i < videos.size(); i++) videos[i].clear();
	}

	void slide::initSelect() {
		canRefresh = true;
		//for (Uint32 i = 0; i < videos.size(); i++) videos[i].resetInterrupt();
		/* @OldCode
		for (int i = 0; i < images.size(); i++) {
			// @TODO
			// condition to see if elements are only for some moments visible, not from the start
			images[i].setMaxAlpha();
		}

		for (int i = 0; i < textLines.size(); i++) {
			textLines[i].setMaxAlpha();
		}

		for (int i = 0; i < videos.size(); i++) {
			videos[i].setMaxAlpha();
		}
		*/
	}

	void slide::clearScreen(SDL_Renderer* renderer){
		SDL_SetRenderDrawColor(renderer, backgroundColor.x, backgroundColor.y, backgroundColor.z, 255);
		SDL_RenderClear(renderer);
	}

	void slide::renderComponents(SDL_Renderer* renderer){
		for (Uint32 i = 0; i < images.size(); i++) images[i].render();
		for (Uint32 i = 0; i < textLines.size(); i++) textLines[i].render();
		for (Uint32 i = 0; i < rects.size(); i++) rects[i].render();
	}

	void slide::noRefresh() {
		canRefresh = false;
	}

}