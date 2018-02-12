//	cshow a simple slide show program.
//
//	Copyright (C) 2018 Streanga Sarmis-Stefan<streangasarmis@gmail.com>
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

#include "vec3.h"

namespace cshow {

	vec3 vec3::zero = vec3();

	vec3::vec3():x(0), y(0), z(0) {}
	vec3::vec3(int x, int y, int z):x(x), y(y), z(z) {}

	vec3& vec3::add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	
	vec3& vec3::substract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	
	vec3& vec3::multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	
	vec3& vec3::divide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3 operator+(vec3 left, const vec3& right) {
		return (left.add(right));
	}

	vec3 operator-(vec3 left, const vec3& right) {
		return (left.add(right));
	}
	
	vec3 operator*(vec3 left, const vec3& right) {
		return (left.add(right));
	}

	vec3 operator/(vec3 left, const vec3& right) {
		return (left.add(right));
	}

	bool operator==(const vec3& left, const vec3& right) {
		return (left.x == right.x && left.y == right.y && left.z == right.z);
	}

	std::ostream& operator<<(std::ostream& os, const vec3& vec) {
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

}