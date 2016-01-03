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

#ifndef CORE_COREENGINE_H_
#define CORE_COREENGINE_H_

/***************************************************************************************************
 * This header is intended to be included by any game as it provides access to the whole
 * engine and everything required to make it work
 ***************************************************************************************************/

/* Include all of the necessary headers from the environment */
#include <windows.h>
#include <GL/GLEW/glew.h>
#include <GL/GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>

/* Include the needed parts of the engine */
#include "../utils/StringUtils.h"
#include "../utils/MathUtils.h"
#include "../utils/Logging.h"
#include "../utils/FileUtils.h"
#include "../utils/FPSUtils.h"
#include "../utils/GLUtils.h"
#include "../utils/Time.h"
#include "../utils/Timer.h"
#include "BaseEngine.h"
#include "render/Shader.h"
#include "render/Renderer.h"
#include "render/Scene.h"
#include "ResourceLoader.h"
#include "Settings.h"
#include "Mesh.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "game/DebugCamera.h"
#include "Skybox.h"
#include "Model.h"
#include "Window.h"

/***************************************************************************************************/

#endif
