//	cshow a simple slide show program.
//
//	Copyright (C) 2017 Streanga Sarmis-Stefan<streangasarmis@gmail.com>
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

#include <iostream> // for ostream

namespace cshow {

	struct vec3 {
		
		int x, y, z;

		static vec3 zero;

		vec3();
		vec3(int x, int y, int z);

		vec3& add(const vec3& other);
		vec3& substract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);
		friend bool operator==(const vec3& left, const vec3& right);
		friend std::ostream& operator<<(std::ostream& os, const vec3& vec);
	};

}