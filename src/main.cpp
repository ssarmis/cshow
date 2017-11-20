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

#include <SDL.h>
#include <iostream>

#include "window.h"
#include "app.h"

#ifdef _WIN32
#undef main
#endif

int main(int argc, char *argv[]) {

	if (argc == 1) {
		std::cout << "Usage " << argv[0] << " filename" << std::endl;
		system("pause");
		return 1;
	}

	cshow::slidefilereader reader(argv[1]);
	cshow::window sdlWindow(reader.processHeader());
	cshow::app App;

	App.run(sdlWindow, reader);

	return 0;
}