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

#define TEST_LIGHTING

#ifdef TEST_LIGHTING
#include "LightingTest.h"

int main() {
	LightingTest game;
	game.create();
	return 0;
}
#endif

#ifdef TEST_GUI
#include "GUITest.h"

int main() {
	GUITest game;
	game.create();
	return 0;
}
#endif

#ifdef TEST_WINDOW
#include "WindowTest.h"

int main() {
	WindowTest game;
	game.create();
	return 0;
}
#endif
