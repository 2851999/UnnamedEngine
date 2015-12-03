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

#include <iostream>
#include "Time.h"
#include "FPSCalculator.h"

/***************************************************************************************************
 * The FPSCalculator class
 ***************************************************************************************************/

FPSCalculator::FPSCalculator() {
	m_mode = MODE_FPS_PER_SECOND;
	m_currentDeltaTime = 0;
	m_currentFPS = 0;
	m_started = false;
	m_lastDeltaFrameTime = 0;
	m_lastFrameTime = 0;
	m_fpsCount = 0;
}

FPSCalculator::FPSCalculator(unsigned int mode) {
	m_mode = mode;
	m_currentDeltaTime = 0;
	m_currentFPS = 0;
	m_started = false;
	m_lastDeltaFrameTime = 0;
	m_lastFrameTime = 0;
	m_fpsCount = 0;
}

void FPSCalculator::update() {
	if (! m_started) {
		m_lastFrameTime = Time::getTimeMilliseconds();
		m_lastDeltaFrameTime = Time::getTimeMilliseconds();
		m_started = true;
	}
	if (m_mode != MODE_FPS_OFF) {
		long current = Time::getTimeMilliseconds();
		if (m_mode == MODE_FPS_PER_FRAME) {
			m_currentDeltaTime = current - m_lastDeltaFrameTime;
			m_lastDeltaFrameTime = current;
			if (m_currentDeltaTime != 0)
				m_currentFPS = (int) (1000.0f / m_currentDeltaTime);
		} else if (m_mode == MODE_FPS_PER_SECOND) {
			m_currentDeltaTime = current - m_lastDeltaFrameTime;
			m_lastDeltaFrameTime = current;
			m_fpsCount ++;
			if ((current - m_lastFrameTime) >= 1000) {
				m_lastFrameTime = current;
				m_currentFPS = m_fpsCount;
				m_fpsCount = 0;
			}
		}
	}
}

void FPSCalculator::reset() {
	m_currentDeltaTime = 0;
	m_currentFPS = 0;
	m_started = false;
	m_lastDeltaFrameTime = 0;
	m_lastFrameTime = 0;
}

/***************************************************************************************************/
