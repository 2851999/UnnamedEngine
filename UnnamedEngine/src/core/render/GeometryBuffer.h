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

#ifndef CORE_RENDER_GEOMETRYBUFFER_H_
#define CORE_RENDER_GEOMETRYBUFFER_H_

#include "FBO.h"

/***************************************************************************************************
 * The GeometryBuffer class
 ***************************************************************************************************/

class GeometryBuffer {
private:
	FBO* m_fbo;
public:
	/* The various buffers */
	static const int BUFFER_POSITION = 0;
	static const int BUFFER_COLOUR   = 1;
	static const int BUFFER_NORMAL   = 2;
	static const int BUFFER_DEPTH    = 3;

	GeometryBuffer();

	inline RenderTexture* getTexture(int texture) { return m_fbo->getTexture(texture); }
	inline void bind() { m_fbo->bind(); }
	inline void unbind() { m_fbo->unbind(); }
};

/***************************************************************************************************/

#endif /* CORE_RENDER_GEOMETRYBUFFER_H_ */
