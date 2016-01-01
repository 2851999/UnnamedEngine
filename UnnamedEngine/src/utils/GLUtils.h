/*****************************************************************************
 *
 *   Copyright 2015 - 2016 Joel Davies
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

#ifndef CORE_GLUTILS_H_
#define CORE_GLUTILS_H_

/***************************************************************************************************
 * Methods used to convert regular primitive type values into a value that is used by OpenGL
 * and vice versa
 ***************************************************************************************************/

inline int gl_getValue(bool value) {
	if (value)
		return GL_TRUE;
	else
		return GL_FALSE;
}

inline bool gl_getBooleanValue(int value) {
	if (value == GL_TRUE)
		return true;
	else
		return false;
}

/***************************************************************************************************/

#endif
