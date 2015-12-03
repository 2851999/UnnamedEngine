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

#ifndef UTILS_CLIPBOARDUTILS_H_
#define UTILS_CLIPBOARDUTILS_H_

#include <string>

/***************************************************************************************************
 * The ClipboardUtils class
 ***************************************************************************************************/

class ClipboardUtils {
public:
	static void setText(std::string text);
	static std::string getText();
};

/***************************************************************************************************/

#endif /* UTILS_CLIPBOARDUTILS_H_ */
