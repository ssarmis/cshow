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

#include "cshowutil.h"

namespace cshow {

	// @FromFuture sadly, it didn't get implemented
	int32_t LIST_SIZE = -1;
	vec2 LIST_VEC2(-1, -1);

	int32_t NULL_SIZE = -1;
	vec2 NULL_VEC2(-1, -1);
	vec3 NULL_VEC3(-1, -1, -1);

	vec2 DEFAULT_VEC2(0, 0);
	vec3 DEFAULT_VEC3(0, 0, 0);

	std::map<std::string, int> ivariablesMap;
	std::map<std::string, vec2> v2variablesMap;
	std::map<std::string, vec3> v3variablesMap;

	// @TODO maybe change the return type to bool and see
	// if there were any problems in clearing the memory
	template<class T> void cclearv(std::vector<T>& vector) {
		for (uint32_t i = 0; i < vector.size(); i++) vector[i].clear();
		vector.clear();
	}

	std::string sreadfile(const char* path) {
		// @TODO add exception handle, not found, no permission, etc.
		std::cout << "Reading the file" << std::endl;
		char* buffer = NULL;
		std::string result;

		FILE* file = fopen(path, "rt");
		fseek(file, 0, SEEK_END);
		uint32_t size = ftell(file);
		buffer = new char[size + 1];
		memset(buffer, 0, size + 1);
		fseek(file, 0, SEEK_SET);
		fread(buffer, 1, size, file);
		fclose(file);

		result = std::string(buffer);

		delete[] buffer;

		return result;
	}

	bool icheckArgumentVals(uint32_t& toChange, const std::string& line, uint32_t index) {
		index++;
		int32_t arg[1] = { -1 }; // how many args
		int32_t r[1] = { false }; // wich one has a variable as parameter

		uint32_t tmpIndex = index;
		std::stringstream ss(line.substr(++index, line.size()));

		for (uint32_t i = 0; i < 1; i++) {
			while ((line[tmpIndex] == ' ' || line[tmpIndex] == '\t')) tmpIndex++; // skips spaces and tabs
			if (line[tmpIndex] == '$') {
				r[i] = true;
				std::string variableName;
				std::stringstream getName(line.substr(++tmpIndex, line.size()));
				getName >> variableName;
				arg[i] = ivariablesMap[variableName];
				if (ivariablesMap.find(variableName) == ivariablesMap.end())  std::cout << variableName << " could not be found." << std::endl;
			}
			while (line[tmpIndex] != '$' && line[tmpIndex] != ':' && line[tmpIndex] != '\"' && line[tmpIndex] != '\n' && tmpIndex < line.size()) tmpIndex++;
		}

		if (!r[0])
			ss >> arg[0];

		if (arg[0] == -1) {
			std::cout << "line " << line << " < Please provide 1 argument to the size parameter :)" << std::endl;
			return false;
		}

		toChange = arg[0];
		return true;
	}
	bool v2checkArgumentVals(vec2& toChange, const std::string& line, uint32_t index) {
		bool r[2] = { false, false };
		int32_t arg[2] = { -1, -1 };

		std::stringstream ss(line.substr(++index, line.size()));

		uint32_t tmpIndex = index;

		for (uint32_t i = 0; i < 2; i++) {
			while ((line[tmpIndex] == ' ' || line[tmpIndex] == '\t')) tmpIndex++;
			if (line[tmpIndex] == '$') {
				std::string variableName;
				std::stringstream getName(line.substr(++tmpIndex, line.size()));
				getName >> variableName;
				if (ivariablesMap.find(variableName) != ivariablesMap.end()) {
					r[i] = true;
					arg[i] = ivariablesMap[variableName];
				}
				else if (v2variablesMap.find(variableName) != v2variablesMap.end()) {
					r[0] = true;
					r[1] = true;
					arg[0] = v2variablesMap[variableName].x;
					arg[1] = v2variablesMap[variableName].y;
					break;
				}
				else std::cout << variableName << " could not be found." << std::endl;
				tmpIndex += variableName.size();
			}
			while (line[tmpIndex] != '$' && line[tmpIndex] != ':' && line[tmpIndex] != '\"' && line[tmpIndex] != '\n' && tmpIndex < line.size()) tmpIndex++;
		}

		std::string garbage;
		if (r[0] && r[1]) {}
		else if (r[0] && !r[1]) ss >> garbage >> arg[1];
		else if (!r[0] && r[1]) ss >> arg[0];
		else ss >> arg[0] >> arg[1];

		if (arg[0] == -1 || arg[1] == -1) {
			std::cout << "line " << line << " < Please provide 2 numbers to the parameter :)" << arg[0] << arg[1] << std::endl;
			return false;
		}
		toChange = vec2(arg[0], arg[1]);
		return true;
	}
	bool v3checkArgumentVals(vec3& toChange, const std::string& line, uint32_t index) {
		std::stringstream ss(line.substr(++index, line.size()));
		uint32_t tmpIndex = index;

		bool r[3] = { false, false, false };
		int32_t arg[3] = { -1, -1, -1 };

		for (uint32_t i = 0; i < 3; i++) {
			while ((line[tmpIndex] == ' ' || line[tmpIndex] == '\t')) tmpIndex++;
			if (line[tmpIndex] == '$') {
				r[i] = true;
				std::string variableName;
				std::stringstream getName(line.substr(++tmpIndex, line.size()));
				getName >> variableName;
				if (ivariablesMap.find(variableName) != ivariablesMap.end()) {
					r[i] = true;
					arg[i] = ivariablesMap[variableName];
				}
				else if (v3variablesMap.find(variableName) != v3variablesMap.end()) {
					r[0] = true;
					r[1] = true;
					r[2] = true;
					arg[0] = v3variablesMap[variableName].x;
					arg[1] = v3variablesMap[variableName].y;
					arg[2] = v3variablesMap[variableName].z;
					break;
				}
				else std::cout << variableName << " could not be found." << std::endl;
				tmpIndex += variableName.size();
			}
			while (line[tmpIndex] != '$' && line[tmpIndex] != ':' && line[tmpIndex] != '\"' && line[tmpIndex] != '\n' && tmpIndex < line.size()) tmpIndex++;
		}

		std::string garbage;
		if (r[0] && r[1] && r[2]) {}
		else if (r[0] && !r[1] && !r[2]) ss >> garbage >> arg[1] >> arg[2];
		else if (!r[0] && r[1] && !r[2]) ss >> arg[0] >> garbage >> arg[2];
		else if (!r[0] && !r[1] && r[2]) ss >> arg[0] >> arg[1] >> garbage;
		else if (r[0] && r[1] && !r[0]) ss >> garbage >> garbage >> arg[2];
		else if (!r[0] && r[1] && r[0]) ss >> arg[0] >> garbage >> garbage;
		else if (r[0] && !r[1] && r[0]) ss >> garbage >> arg[1] >> garbage;
		else ss >> arg[0] >> arg[1] >> arg[2];

		if (arg[0] == -1 || arg[1] == -1 || arg[2] == -1) {
			std::cout << "line " << line << " < Please provide 3 numbers to the parameter :)" << arg[0] << arg[1] << arg[2] << std::endl;
			return false;
		}
		toChange = vec3(arg[0], arg[1], arg[2]);
		return true;
	}
	
	void checkTextLineParams(const std::string& line, uint32_t index, std::string& text, vec3& background, vec3& color, vec2& position, uint32_t& size) {
		switch (line[index]) {
		case 's': {
			if (!icheckArgumentVals(size, line, index));
			break;
		}
		case 'p': {
			if (!v2checkArgumentVals(position, line, index)); // If I wan't I can see if it didn't work and do something, idk, it return -1 if something's not ok
			break;
		}
		case 'c': {
			if (!v3checkArgumentVals(color, line, index));
			break;
		}
		case 'b': {
			if (!v3checkArgumentVals(background, line, index));
			break;
		}

		default:
			break;
		}
	}
	void checkImageParams(const std::string& line, uint32_t index, vec2& position, vec2& size) {
		switch (line[index]) {
		case 's': {
			if (!v2checkArgumentVals(size, line, index));
			break;
		}
		case 'p': {
			if (!v2checkArgumentVals(position, line, index)); // If I want I can see if it didn't work and do something, idk, it returns -1 if something's not ok
			break;
		}
		default:
			break;
		}
	}
	void checkVideoParams(const std::string& line, uint32_t index, vec2& position, vec2& size) {
		switch (line[index]) {
		case 's': {
			if (!v2checkArgumentVals(size, line, index));
			break;
		}
		case 'p': {
			if (!v2checkArgumentVals(position, line, index)); // If I want I can see if it didn't work and do something, idk, it returns -1 if something's not ok
			break;
		}
		default:
			break;
		}
	}
	void checkColorParams(const std::string& line, uint32_t index, vec3& color) {
		switch (line[index]) {
			case 'c': {
				if (!v3checkArgumentVals(color, line, index));
				break;
			}
			default: 
				break;
		}
	}
	void checkRectParams(const std::string& line, uint32_t index, vec2& position, vec3& background, vec2& size) {
		switch (line[index]) {
		case 's': {
			if (!v2checkArgumentVals(size, line, index));
			break;
		}
		case 'p': {
			if (!v2checkArgumentVals(position, line, index)); // If I wan't I can see if it didn't work and do something, idk, it return -1 if something's not ok
			break;
		}
		case 'c': {
			if (!v3checkArgumentVals(background, line, index));
			break;
		}

		default:
			break;
		}
	}

	void interpretSlideCode(SDL_Renderer* renderer, slide& currentSlide, const std::string& line) {
		// @TODO need to change this... so that it does ignore '#'
		// add tab allower so that some lines can start with multiple tabs
		if (line[0] == ':') {
			uint32_t strIndex = 1;

			switch (line[strIndex]) {

				case 't': { // weird goto behaivour
					// @TODO fix the : after " being considered a parameter
					std::string text;
					uint32_t size;
					vec3 color = NULL_VEC3;
					vec3 background = NULL_VEC3;
					vec2 position = NULL_VEC2;

					uint32_t st = line.find("\"");
					uint32_t fn = line.find("\"", st + 2);
					uint32_t index = 0;

					std::istringstream cpy(line);
					std::string wline;

					std::stringstream ss;
				
					while (std::getline(cpy, wline, ':') && index < st){
						index += wline.size();
						checkTextLineParams(wline, 0, text, background, color, position, size);
					}
				
					for (uint32_t i = st + 1; i < fn; i++) ss << line[i];
					text = ss.str();

					// If needed to change the default values, heres where
					if (color == NULL_VEC3) color = DEFAULT_VEC3; else DEFAULT_VEC3 = color;
					if (position == NULL_VEC2) position = DEFAULT_VEC2; else DEFAULT_VEC2 = position;

					currentSlide.staticComponents.emplace_back(new textline(renderer, text, background, color, position, size));

					break;
				}

				case 'b': { // weird goto behaivour
					vec3 color = NULL_VEC3;

					std::istringstream cpy(line);
					std::string wline;

					std::stringstream ss;

					while (std::getline(cpy, wline, ':'))
						checkColorParams(wline, 0, color);

					if (color == NULL_VEC3) color = DEFAULT_VEC3; else DEFAULT_VEC3 = color;

					currentSlide.setBackground(color);

					break;
				}

				case 'i': { // weird goto behaivour
					std::string path;
					vec2 position = NULL_VEC2;
					vec2 size = NULL_VEC2;

					uint32_t st = line.find("\"");
					uint32_t fn = line.find("\"", st + 2);
					uint32_t index = 0;

					std::istringstream cpy(line);
					std::string wline;

					std::stringstream ss;

					while (std::getline(cpy, wline, ':') && index < st) {
						index += wline.size();
						checkImageParams(wline, 0, position, size);
					}

					for (uint32_t i = st + 1; i < fn; i++) ss << line[i];
					path = ss.str();

					if (size == NULL_VEC2) size = DEFAULT_VEC2; else DEFAULT_VEC2 = size;
					if (position == NULL_VEC2) position = DEFAULT_VEC2; else DEFAULT_VEC2 = position;

					currentSlide.staticComponents.emplace_back(new image(renderer, path, position, size));

					break;
				}

				case 'v': { // weird goto behaivour
					if (line[strIndex + 1] == 'i') {
						std::string path;
						vec2 position = NULL_VEC2;
						vec2 size = NULL_VEC2;

						uint32_t st = line.find("\"");
						uint32_t fn = line.find("\"", st + 2);
						uint32_t index = 0;

						std::istringstream cpy(line);
						std::string wline;

						std::stringstream ss;

						while (std::getline(cpy, wline, ':') && index < st) {
							index += wline.size();
							checkVideoParams(wline, 0, position, size);
						}

						for (uint32_t i = st + 1; i < fn; i++) ss << line[i];
						path = ss.str();

						if (size == NULL_VEC2) size = DEFAULT_VEC2; else DEFAULT_VEC2 = size;
						if (position == NULL_VEC2) position = DEFAULT_VEC2; else DEFAULT_VEC2 = position;

						currentSlide.dynamicComponents.emplace_back(new video(renderer, path, position, size));
						//currentSlide.noRefresh();
					}
					break;

				}

				case 'r': { // weird goto behaivour
					vec3 color = NULL_VEC3;
					vec3 background = NULL_VEC3;
					vec2 position = NULL_VEC2;
					vec2 size = NULL_VEC2;

					std::istringstream cpy(line);
					std::string wline;

					std::stringstream ss;

					while (std::getline(cpy, wline, ':')) {
						checkRectParams(wline, 0, position, background, size);
					}

					// If needed to change the default values, heres where
					if (color == NULL_VEC3) color = DEFAULT_VEC3; else DEFAULT_VEC3 = color;
					if (position == NULL_VEC2) position = DEFAULT_VEC2; else DEFAULT_VEC2 = position;

					currentSlide.staticComponents.emplace_back(new rectangle(renderer, position, background, size));

					break;
				}

				default:
					break;
				}

		}
	}

	void initializeGlobalVariables(const std::string& line) {
		if (line[0] == ':') {
			uint32_t strIndex = 1;

			switch (line[strIndex]) {
			case 'v': { // weird goto behaivour
				switch (line[strIndex + 1]) {
				case ' ': {
					std::string variableName;
					uint32_t value;

					std::stringstream gv(line.substr(++strIndex, line.size()));
					gv >> variableName;
					strIndex += variableName.size();

					std::stringstream gvv(line.substr(++strIndex, line.size()));
					gvv >> value;

					ivariablesMap.emplace(variableName, value);

					break;
				}

				case '2': {
					strIndex++;
					std::string variableName;
					vec2 value2;

					std::stringstream gv(line.substr(++strIndex, line.size()));
					gv >> variableName;
					strIndex += variableName.size();

					std::stringstream gvv(line.substr(++strIndex, line.size()));
					gvv >> value2.x >> value2.y;

					v2variablesMap.emplace(variableName, value2);
					break;
				}

				case '3': {
					strIndex++;
					std::string variableName;
					vec3 value3;

					std::stringstream gv(line.substr(++strIndex, line.size()));
					gv >> variableName;
					strIndex += variableName.size();

					std::stringstream gvv(line.substr(++strIndex, line.size()));
					gvv >> value3.x >> value3.y >> value3.z;

					v3variablesMap.emplace(variableName, value3);

					break;
				}
				}
            break;
			}

			default:
				break;
			}
		}
	}
}