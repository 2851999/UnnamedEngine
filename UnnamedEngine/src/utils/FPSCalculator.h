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

#ifndef UTILS_FPSCALCULATOR_H_
#define UTILS_FPSCALCULATOR_H_

/***************************************************************************************************
 * The FPSCalculator class
 ***************************************************************************************************/

class FPSCalculator {
private:
	unsigned int m_mode;
	long m_lastFrameTime;
	long m_lastDeltaFrameTime;
	long m_currentDeltaTime;
	int m_currentFPS;
	int m_fpsCount;
	bool m_started;
public:
	static const unsigned int MODE_FPS_OFF = 0;
	static const unsigned int MODE_FPS_PER_FRAME = 1;
	static const unsigned int MODE_FPS_PER_SECOND = 2;
	FPSCalculator();
	FPSCalculator(unsigned int mode);
	void update();
	void reset();
	void setMode(unsigned int mode) { m_mode = mode; }
	int getMode() { return m_mode; }
	long getDelta() { return m_currentDeltaTime; }
	int getFPS() { return m_currentFPS; }
};

/***************************************************************************************************/

#endif /* UTILS_TIME_H_ */
