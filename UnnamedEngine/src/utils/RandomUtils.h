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

#ifndef UTILS_RANDOMUTILS_H_
#define UTILS_RANDOMUTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

inline void randomInit() {
	srand(static_cast <unsigned> (time(0)));
}

inline float randomFloat() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

inline float randomFloat(float min, float max) {
	return min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
}

inline float randomFloat(float minmax) {
	return -minmax + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (2 * minmax));
}

#endif /* UTILS_RANDOMUTILS_H_ */
