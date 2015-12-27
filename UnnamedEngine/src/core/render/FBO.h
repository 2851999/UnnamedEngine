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

#ifndef CORE_RENDER_FBO_H_
#define CORE_RENDER_FBO_H_

#include <vector>

#include "../Texture.h"

/***************************************************************************************************
 * The FBO class
 ***************************************************************************************************/

class FBO {
private:
	/* The FBO target and pointer */
	GLuint m_target;
	GLuint m_pointer;

	/* The array of attachments that need to be written to */
	GLuint* m_attachments;

	/* The number of attachments */
	unsigned int m_numAttachments;

	/* The various buffers (textures) in this FBO */
	std::vector<RenderTexture*> m_textures;

public:
	FBO(GLuint target);

	inline void add(RenderTexture* texture) { m_textures.push_back(texture); }

	void setup();

	void bind();
	void unbind();

	inline RenderTexture* getTexture(int texture) { return m_textures.at(texture); }
	inline unsigned int getNumAttachments() { return m_numAttachments; }
};

/***************************************************************************************************/

#endif /* CORE_RENDER_FBO_H_ */
