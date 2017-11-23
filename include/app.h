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

#define KB(x) ((1 << 10) * (x))

#include <SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <memory>
#include <list>

#include "window.h"
#include "rectangle.h"
#include "slidemanager.h"
#include "slidefilereader.h"

namespace cshow {

    class app {

        private:
            int32_t                 x[1], y[1];
            rectangle               mouseRect;
	        SDL_Cursor*             cursor;
            SDL_Surface*            cursorSurface;
            SDL_Renderer*           renderer;
            slidemanager*           manager;
            std::list<rectangle*>   trace;

        public:
            
            app(slidemanager* manager);
            ~app();

            void run(const char* path, window& sdlWindow, const slidefilereader& reader);
            void render();


    };

}