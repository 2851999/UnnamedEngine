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

#ifndef CORE_SPRITE_H_
#define CORE_SPRITE_H_

#include "../utils/Timer.h"
#include "Object.h"

/***************************************************************************************************
 * The TextureEntity2D class
 ***************************************************************************************************/

class TextureEntity2D : public RenderableObject2D {
public:
	/* The constructors */
	TextureEntity2D(Texture* texture, Colour colour, float width, float height) : RenderableObject2D(MeshBuilder::createQuad(width, height, texture, colour), width, height) {
		m_mesh->setTexture(texture);
	}
	TextureEntity2D(Texture* texture, float width, float height) : TextureEntity2D(texture, Colour::WHITE, width, height) {}
	TextureEntity2D(Texture* texture, Colour colour) : TextureEntity2D(texture, colour, texture->getWidth(), texture->getHeight()) {}
	TextureEntity2D(Texture* texture) : TextureEntity2D(texture, Colour::WHITE, texture->getWidth(), texture->getHeight()) {}

	void setTexture(Texture* texture);
};

/***************************************************************************************************/

/***************************************************************************************************
 * The Animation2D class
 ***************************************************************************************************/

class Animation2D {
private:
	/* The entity */
	RenderableObject2D* m_entity = NULL;

	/* The time between each frame of the animation */
	int m_timeBetweenFrame = 0;

	/* The timer */
	Timer* m_timer = NULL;

	/* The current frame */
	int m_currentFrame = 0;

	/* States whether the animation is running */
	bool m_running = false;

	/* States whether the animation will repeat when finished */
	bool m_repeat = false;
public:
	/* The constructors */
	Animation2D(RenderableObject2D* entity, int timeBetweenFrame, bool repeat = false) {
		m_entity = entity;
		m_timeBetweenFrame = timeBetweenFrame;
		m_repeat = repeat;
		m_timer = new Timer();
	}

	virtual ~Animation2D() {

	}

	/* The method used to update this animation */
	void update();

	/* The methods called during the course of an animation */
	virtual void startAnimation() {}
	virtual void updateAnimation() {}
	virtual void stopAnimation() {}
	virtual void resetAnimation() {}

	virtual bool hasFinished() { return true; }

	/* The method used to start this animation */
	void start();

	/* The method used to stop this animation */
	void stop();

	/* The method used to reset this animation */
	void reset();

	/* The method used to restart this animation */
	void restart();

	/* The method used to pause this animation */
	inline void pause() {
		m_timer->pause();
	}

	/* The method used to resume this animation */
	inline void resume() {
		m_timer->resume();
	}

	/* The setters and getters */
	inline void setEntity(RenderableObject2D* entity) { m_entity = entity; }
	inline void setTimeBetweenFrame(int timeBetweenFrame) { m_timeBetweenFrame = timeBetweenFrame; }
	inline void setRepeat(bool repeat) { m_repeat = repeat; }
	inline RenderableObject2D* getEntity() { return m_entity; }
	inline int getTimeBetweenFrame() { return m_timeBetweenFrame; }
	inline int getCurrentFrame() { return m_currentFrame; }
	inline bool isRunning() { return m_running; }
	inline bool getRepear() { return m_repeat; }
};

/***************************************************************************************************/

/***************************************************************************************************
 * The TextureAnimation2D class
 ***************************************************************************************************/

class TextureAnimation2D : public Animation2D {
private:
	/* The textures */
	std::vector<Texture*> m_textures;
	Texture* m_tileSet = NULL;

	/* The data for a tile set animation */
	int m_currentTile = 0;
	float m_tileSetWidth = 0;
	float m_tileSetHeight = 0;
	float m_tileWidth = 0;
	float m_tileHeight = 0;
	int m_tilesPerRow = 0;
	int m_tilesPerColumn = 0;
	int m_numberOfTiles = 0;
public:
	/* The constructors */
	TextureAnimation2D(RenderableObject2D* entity, std::vector<Texture*> textures, int timeBetweenFrame, bool repeat = false) :
		Animation2D(entity, timeBetweenFrame, repeat) {
		m_textures = textures;
	}

	TextureAnimation2D(RenderableObject2D* entity, Texture* tileSet, int tilesPerRow, int tilesPerColumn, int timeBetweenFrame, bool repeat = false) :
		Animation2D(entity, timeBetweenFrame, repeat) {
		m_tileSet = tileSet;
		m_currentTile = -1;
		m_tileSetWidth = tileSet->getWidth();
		m_tileSetHeight = tileSet->getHeight();
		m_tileWidth = m_tileSetWidth / (float) tilesPerRow;
		m_tileHeight = m_tileSetHeight / (float) tilesPerRow;
		m_tilesPerRow = tilesPerRow;
		m_tilesPerColumn = tilesPerColumn;
		m_numberOfTiles = tilesPerRow * tilesPerColumn;
	}

	void updateAnimation() override;
	void resetAnimation() override;

	bool hasFinished() override;
};

/***************************************************************************************************/

/***************************************************************************************************
 * The Sprite2D class
 ***************************************************************************************************/

class Sprite2D : public TextureEntity2D {
private:
	/* The animations */
	std::map<std::string, Animation2D*> m_animations;

	/* The running animation */
	Animation2D* m_currentAnimation = NULL;
public:
	/* The constructors */
	Sprite2D(Texture* texture, Colour colour, float width, float height) :
		TextureEntity2D(texture, colour, width, height) {
	}

	Sprite2D(Texture* texture, float width, float height) :
		TextureEntity2D(texture, Colour::WHITE, width, height) {
	}

	Sprite2D(Texture* texture, Colour colour = Colour::WHITE) :
		Sprite2D(texture, colour, texture->getWidth(), texture->getHeight()) {
	}

	/* The method used to update this sprite */
	void update() override;

	/* The method used to start an animation given the name */
	void start(std::string name);

	/* The method used to add an animation */
	inline void add(Animation2D* animation, std::string name) {
		m_animations.insert(std::pair<std::string, Animation2D*>(name, animation));
	}
};

/***************************************************************************************************/

#endif /* CORE_SPRITE_H_ */
