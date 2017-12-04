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
#include <string.h>
#include <vector> 
#include <map>

#include "slide.h"
#include "textline.h"
#include "image.h"
#include "video.h"

namespace cshow {

	template<class T> void cclearv(std::vector<T>& vector);
	std::string sreadfile(const char* path);

	bool icheckArgumentVals(uint32_t& toChange, const std::string& line, uint32_t index);
	bool v3checkArgumentVals(vec3& toChange, const std::string& line, uint32_t index);
	bool v2checkArgumentVals(vec2& toChange, const std::string& line, uint32_t index);

	void checkTextLineParams(const std::string& line, uint32_t index, std::string& text, vec3& background, vec3& color, vec2& position, uint32_t& size);
	void checkImageParams(const std::string& line, uint32_t index, vec2& position, vec2& size);
	void checkVideoParams(const std::string& line, uint32_t index, vec2& position, vec2& size);
	void checkColorParams(const std::string& line, uint32_t index, vec3& color);

	void interpretSlideCode(SDL_Renderer* renderer, const std::string& fontPath, slide* currentSlide, const std::string& line);
	void initializeGlobalVariables(const std::string& line);

}