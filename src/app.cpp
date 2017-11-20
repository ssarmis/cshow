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

#include "app.h"

namespace cshow {

    void app::run(window& sdlWindow, const slidefilereader& reader){
        SDL_Event event;
        
        renderer = SDL_CreateRenderer(sdlWindow.getWindow(), -1, SDL_RENDERER_ACCELERATED);
        
        cursorSurface = IMG_Load("cursor.png");
	    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);

	    SDL_SetCursor(cursor);
	    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		reader.proccessFile(renderer, sdlWindow.getWidth(), sdlWindow.getHeight());

		while (sdlWindow.getRunning()) {
			SDL_Delay(1000 / 100); // reducing cpu usage ALOT, poor way to handle frame rate

			while (SDL_PollEvent(&event)) {
				slidemanager::getCurrentSlide().eventHandling(event);

				switch (event.type) {
					case SDL_KEYUP:
						break;

					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_RIGHT) {
							slidemanager::nextSlide();
						}

						if (event.key.keysym.sym == SDLK_LEFT) {
							slidemanager::previousSlide();
						}
						break;
					case SDL_QUIT:
						sdlWindow.setRunning(false);
						break;
				}
			}
			
			render();
		}

    }

    void app::render() {
	
        if(SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            trace.emplace_back(rectangle(renderer, vec2(*x, *y), vec3(255, 0, 0), vec2(3, 3)));

        if (trace.size() * sizeof(rectangle) > KB(32)) trace.pop_front();
        // @TODO need to free whats in the rectangle
        if (SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
            trace.clear();
            slidemanager::getCurrentSlide().clearScreen(renderer);
        } 

        slidemanager::getCurrentSlide().render(renderer);

        for (std::list<rectangle>::iterator i = trace.begin(); i != trace.end(); i++)
            ((rectangle)*i).render();

        SDL_RenderPresent(renderer);
    }

    app::~app(){
	    SDL_FreeCursor(cursor);
    	SDL_FreeSurface(cursorSurface);
    }

}