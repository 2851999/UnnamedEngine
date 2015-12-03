/*****************************************************************************
 *
 *   Copyright 2015 Joel Davies
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *****************************************************************************/

#include "Rectangle.h"

/***************************************************************************************************
 * The Rectangle class
 ***************************************************************************************************/

Rect::Rect() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rect::Rect(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool Rect::contains(float x, float y) {
	return (x >= this->x && y >= this->y && x <= this->x + this->width && y <= this->y + this->height);
}

bool Rect::intersects(float x, float y) {
	return (x >= this->x && y >= this->y && x <= this->x + this->width && y <= this->y + this->height);
}

bool Rect::intersects(Rect other) {
	return intersects(other.x, other.y) ||
		   intersects(other.x + other.width, other.y) ||
		   intersects(other.x + other.width, other.y + other.height);
		   intersects(other.x, other.y + other.height) ||
		   other.intersects(x, y) ||
		   other.intersects(x + width, y) ||
		   other.intersects(x + width, y + height) ||
		   other.intersects(x, y + height);
}

/***************************************************************************************************/
