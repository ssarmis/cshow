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

#pragma once

#include <sstream>
#include <string>
#include <SDL.h>

#include "slide.h"
#include "slidemanager.h"
#include "cshowutil.h"
#include "vec3.h"

namespace cshow {

	class slidefilereader {

		private:
			slidemanager* 	manager;
			bool			debug;
			std::string	file;

		public:
			slidefilereader(slidemanager* manager, const char* path);
			vec3 processHeader() const;
			void proccessFile(SDL_Renderer* renderer, const std::string& fontPath, uint32_t width, uint32_t height) const;
	};

}
