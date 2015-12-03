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

#ifndef CORE_GUI_GUILOADINGBAR_H_
#define CORE_GUI_GUILOADINGBAR_H_

#include "GUIComponent.h"

/***************************************************************************************************
 * The GUILoadingBar class
 ***************************************************************************************************/

class GUILoadingBar : public GUIComponent {
public:
	unsigned int loadingStages;
	unsigned int currentLoadingStage;
	GUIFill* barFill;

	GUILoadingBar(int loadingStages, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
		this->loadingStages = loadingStages;
		currentLoadingStage = 0;
		renderer->colours.push_back(Colour::WHITE);
		barFill = new GUIFill(this, Colour::WHITE);
	}

	GUILoadingBar(int loadingStages, Colour colour, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, Colour::WHITE), width, height)) {
		this->loadingStages = loadingStages;
		currentLoadingStage = 0;
		renderer->colours.push_back(colour);
		barFill = new GUIFill(this, Colour::WHITE);
	}

	GUILoadingBar(int loadingStages, Texture* texture, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, texture, Colour::WHITE), width, height)) {
		this->loadingStages = loadingStages;
		currentLoadingStage = 0;
		renderer->colours.push_back(Colour::WHITE);
		renderer->textures.push_back(texture);
		barFill = new GUIFill(this, Colour::WHITE);
	}

	GUILoadingBar(int loadingStages, Texture* texture, Colour colour, float width, float height) :
		GUIComponent(new RenderableObject2D(MeshBuilder::createQuad(width, height, texture, Colour::WHITE), width, height)) {
		this->loadingStages = loadingStages;
		currentLoadingStage = 0;
		renderer->colours.push_back(colour);
		renderer->textures.push_back(texture);
		barFill = new GUIFill(this, Colour::WHITE);
	}

	virtual void stageChanged() {}

	void updateComponent() override { barFill->update(); }
	void renderComponent() override;

	void completedStage();

	inline bool hasCompleted() { return currentLoadingStage == loadingStages; }
	inline float getPercentageComplete() { return (float)((float) currentLoadingStage / (float) loadingStages) * 100; }

	void setBackgroundColour(Colour colour);
	Colour getBackgroundColour();
	void setFillColour(Colour colour);
	Colour getFillColour();
	void setBackgroundTexture(Texture* texture);
	Texture* getBackgroundTexture();
	void setFillTexture(Texture* texture);
	Texture* getFillTexture();
	inline void setCurrentStage(unsigned int stage);
	inline unsigned int getCurrentStage() { return currentLoadingStage; }

	inline bool hasBackgroundColour() { return renderer->colours.size() > 0; }
	inline bool hasBackgroundTexture() { return renderer->textures.size() > 0; }
	inline bool hasFillColour() { return barFill->colour.getR() != -1; }
	inline bool hasFillTexture() { return barFill->texture != NULL; }
};

/***************************************************************************************************/

#endif /* CORE_GUI_GUILOADINGBAR_H_ */
