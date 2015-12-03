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

#ifndef CORE_MATHUTILS_H_
#define CORE_MATHUTILS_H_

#include<math.h>

#define PI 3.14159265

inline float to_radians(float degrees) {
	return (float) degrees * (PI / 180);
}

inline float to_degrees(float radians) {
	return (float) radians * (180 / PI);
}

inline float clamp(float value, float min, float max) {
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

#endif
