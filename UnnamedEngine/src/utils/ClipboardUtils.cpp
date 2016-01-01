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

#include <windows.h>
#include <iostream>
#include <string>
#include "ClipboardUtils.h"

/***************************************************************************************************
 * The ClipboardUtils class
 ***************************************************************************************************/

void ClipboardUtils::setText(std::string text) {
	HGLOBAL x;
	char* y;
	x = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, 0x64);
	y = (char*) GlobalLock(x);
	strcpy(y, text.c_str());
	GlobalUnlock(x);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, x);
	CloseClipboard();
}

std::string ClipboardUtils::getText() {
	OpenClipboard(NULL);
	HANDLE pText = GetClipboardData(CF_TEXT);
	CloseClipboard();
	LPVOID text = GlobalLock(pText);
	return std::string((char*) text);
}

/***************************************************************************************************/
