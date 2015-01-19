/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <SDL2pp/Point.hh>

#include <SDL2pp/Rect.hh>

namespace SDL2pp {

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(const SDL_Point& point) {
	x = point.x;
	y = point.y;
}

Point::Point(int nx, int ny) {
	x = nx;
	y = ny;
}

bool Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}

int Point::GetX() const {
	return x;
}

Point& Point::SetX(int nx) {
	x = nx;
	return *this;
}

int Point::GetY() const {
	return y;
}

Point& Point::SetY(int ny) {
	y = ny;
	return *this;
}

Point Point::operator+(const Point& other) const {
	return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
	return Point(x - other.x, y - other.y);
}

Point Point::operator/(int value) const {
	return Point(x / value, y / value);
}

Point Point::operator*(int value) const {
	return Point(x * value, y * value);
}

Point& Point::operator+=(const Point& other) {
	x += other.x;
	y += other.y;

	return *this;
}

Point& Point::operator-=(const Point& other) {
	x -= other.x;
	y -= other.y;

	return *this;
}

Point& Point::operator/=(int value) {
	x /= value;
	y /= value;

	return *this;
}

Point& Point::operator*=(int value) {
	x *= value;
	y *= value;

	return *this;
}

Point Point::GetClamped(const Rect& rect) const {
	Point p = *this;
	p.Clamp(rect);
	return p;
}

Point& Point::Clamp(const Rect& rect) {
	if (x < rect.x)
		x = rect.x;
	if (x > rect.GetX2())
		x = rect.GetX2();
	if (y < rect.y)
		y = rect.y;
	if (y > rect.GetY2())
		y = rect.GetY2();
	return *this;
}

Point Point::GetWrapped(const Rect& rect) const {
	Point p = *this;
	p.Wrap(rect);
	return p;
}

Point& Point::Wrap(const Rect& rect) {
	if (x < rect.x)
		x = rect.x + rect.w - 1 - (rect.x - x + rect.w - 1) % rect.w;
	else if (x >= rect.x + rect.w)
		x = rect.x + (x - rect.x - rect.w) % rect.w;

	if (y < rect.y)
		y = rect.y + rect.h - 1 - (rect.y - y + rect.h - 1) % rect.h;
	else if (y >= rect.y + rect.h)
		y = rect.y + (y - rect.y - rect.h) % rect.h;

	return *this;
}

}
