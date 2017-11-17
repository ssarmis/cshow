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

#include <SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <list>

#include "window.h"
#include "slidemanager.h"
#include "slidefilereader.h"
#include "video.h"
#include "rectangle.h"

#define KB(x) ((1 << 10) * (x))

#ifdef _WIN32
#undef main
#endif

// @CleanUp bad global variables
SDL_Renderer* renderer = NULL;
cshow::rectangle mouseRect;
std::list<cshow::rectangle> trace;
int x[1], y[1];

void render();

int main(int argc, char *argv[]) {

	if (argc == 1) {
		std::cout << "Usage " << argv[0] << " filename" << std::endl;
		system("pause");
		return 1;
	}

	cshow::slidefilereader reader(argv[1]);
	cshow::window sdlWindow(reader.processHeader());

	renderer = SDL_CreateRenderer(sdlWindow.getWindow(), -1, SDL_RENDERER_ACCELERATED);
	
	// @CleanUp
	SDL_Surface *surface = NULL;
	SDL_Cursor *cursor = NULL;

	surface = IMG_Load("cursor.png");
	cursor = SDL_CreateColorCursor(surface, 0, 0);

	SDL_SetCursor(cursor);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	sdlWindow.run(renderer, render, reader);

	SDL_FreeCursor(cursor);
	SDL_FreeSurface(surface);

	return 0;
}


void render() {
	
	if(SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_LEFT))
		trace.emplace_back(cshow::rectangle(renderer, cshow::vec2(*x, *y), cshow::vec3(255, 0, 0), cshow::vec2(3, 3)));

	cshow::slidemanager::getCurrentSlide().render(renderer);

	if (trace.size() * sizeof(cshow::rectangle) > KB(32)) trace.pop_front();
	for (std::list<cshow::rectangle>::iterator i = trace.begin(); i != trace.end(); i++)
		((cshow::rectangle)*i).render();

	// @TODO need to free whats in the rectangle
	if (SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_RIGHT)){
		trace.clear();
		// @CleanUp
		cshow::slidemanager::getCurrentSlide().clearScreen(renderer);
		cshow::slidemanager::getCurrentSlide().renderComponents(renderer);
	} 

	SDL_RenderPresent(renderer);
	
}