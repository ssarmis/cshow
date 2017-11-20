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

#include "slidefilereader.h"

namespace cshow {

	slidefilereader::slidefilereader(const char* path) {
		file = sreadfile(path);
	}
	
	vec3 slidefilereader::processHeader() const{
		std::istringstream cpy(file);
		std::string c;

		std::getline(cpy, c, '\n');

		std::string mode = c.substr(c.find(':') + 1);
		// @CleanUp very poor and buggy...
		if (mode[0] == 'f') return vec3();
		else if(mode[0] == 'b'){

			std::string rem = c.substr(11, mode.size());
			std::cout << rem;
			std::stringstream ss(rem);
			uint32_t w, h;

			ss >> w >> h;
			
			return vec3(w, h, 1);
		}

		return vec3();

	}

	void slidefilereader::proccessFile(SDL_Renderer* renderer, uint32_t width, uint32_t height) const{
		// @TODO add debug re-reading
		slidemanager::clearSlides();

		std::istringstream ss(file);
		std::string line;

		bool startInterprating = false;
		slide newSlide(renderer, width, height);
		
		std::getline(ss, line); // skip the first line

		while (std::getline(ss, line)) {
			initializeGlobalVariables(line);
			if (line[0] == ':' && line[1] == 's') startInterprating = true;
			if (startInterprating) interpretSlideCode(renderer, newSlide, line);

			if (line[0] == ':' && line[1] == 'e') {
				slidemanager::pushSlideToQueue(newSlide);
				newSlide = slide(renderer, width, height);
			}
		}
	};

}