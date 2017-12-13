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

#include "vec2.h"

namespace cshow {

	vec2 vec2::zero = vec2();

	vec2::vec2():x(0), y(0) {}
	vec2::vec2(int x, int y):x(x), y(y) {}

	vec2& vec2::add(const vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	
	vec2& vec2::substract(const vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	
	vec2& vec2::multiply(const vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}
	
	vec2& vec2::divide(const vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	vec2 operator+(vec2 left, const vec2& right) {
		return (left.add(right));
	}

	vec2 operator-(vec2 left, const vec2& right) {
		return (left.add(right));
	}
	
	vec2 operator*(vec2 left, const vec2& right) {
		return (left.add(right));
	}

	vec2 operator/(vec2 left, const vec2& right) {
		return (left.add(right));
	}

	bool operator==(const vec2& left, const vec2& right) {
		return (left.x == right.x && left.y == right.y);
	}

	std::ostream& operator<<(std::ostream& os, const vec2& vec) {
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}

}