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

#include "app.h"

namespace cshow {

	app::app(slidemanager* manager):manager(manager){ }

    void app::run(const char* path, window& sdlWindow, const slidefilereader& reader){
        SDL_Event event;
        
		std::string resPath(path, strlen(path) - strlen("cshow.exe"));
		resPath.append("\\res\\");

		std::string cursorPath = resPath;
		cursorPath.append("cursor.png");

        renderer = SDL_CreateRenderer(sdlWindow.getWindow(), -1, SDL_RENDERER_ACCELERATED);
        
        cursorSurface = IMG_Load(cursorPath.c_str());
	    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);

	    SDL_SetCursor(cursor);
	    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		reader.proccessFile(renderer, sdlWindow.getWidth(), sdlWindow.getHeight());

		bool running = sdlWindow.getRunning();

		while (running) {
			SDL_Delay(1000 / 100); // reducing cpu usage ALOT, poor way to handle frame rate

			while (SDL_PollEvent(&event)) {

				switch (event.type) {
					case SDL_KEYUP:
						break;

					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_RIGHT) {
							manager->nextSlide();
						}

						if (event.key.keysym.sym == SDLK_LEFT) {
							manager->previousSlide();
						}

						if (event.key.keysym.sym == SDLK_ESCAPE) {
							// @FixMe
							running = false;
						}

						break;
						
					case SDL_QUIT:
						// @FixMe
						running = false;
						break;
				}
			}

			render();
		}
    }

    void app::render() {
	
        if(SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            trace.emplace_back(new rectangle(renderer, vec2(*x, *y), vec3(255, 0, 0), vec2(3, 3)));

        if (trace.size() * sizeof(rectangle) > KB(32)) trace.pop_front();

		for (std::list<rectangle*>::iterator i = trace.begin(); i != trace.end(); i++)
            ((rectangle*)*i)->render();

        if (SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
			for(auto&& rect : trace) delete rect;
			trace.clear();
            manager->getCurrentSlide()->clearScreen(renderer);
        } 

        manager->getCurrentSlide()->render(renderer);

		SDL_RenderPresent(renderer);

    }

    app::~app(){
		for(auto&& rect : trace) delete[] rect;
		trace.clear();
	    SDL_FreeCursor(cursor);
    	SDL_FreeSurface(cursorSurface);
    }

}