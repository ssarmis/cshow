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

#include "slidemanager.h"

namespace cshow {

	std::vector<slide> slidemanager::slideVector;
	Uint32 slidemanager::index = 0;

	slidemanager::slidemanager() { }

	slide slidemanager::getCurrentSlide() {
		return slideVector[index];
	}

	void slidemanager::pushSlideToQueue(const slide& slide) {
		slideVector.emplace_back(slide);
	}

	void slidemanager::nextSlide() {
		if(index < slideVector.size() - 1) index++;
		slideVector[index].initSelect();
	}

	void slidemanager::previousSlide() {
		if (index > 0) index--;
		slideVector[index].initSelect();
	}

	void slidemanager::clearSlides() {
		for (Uint32 i = 0; i < slideVector.size(); i++) {
			slideVector[i].clear();
		}
		
		slideVector.clear();
	}
}