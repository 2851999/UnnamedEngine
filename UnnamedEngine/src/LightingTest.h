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

#include "core/CoreEngine.h"
#include "core/gui/Font.h"

#include "utils/RandomUtils.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

class LightingTest : public Game {
private:
	Model* model2;
	Model* model;
	DebugCamera3D* camera;
	Scene* scene;
	DirectionalLight* directionalLight;
	PointLight* pointLight;
	SpotLight* spotLight;
	bool wireframe;

	std::vector<PointLight*> pointLights;
public:
	virtual ~LightingTest() {}
	virtual void initialise(Settings* settings);
	virtual void created();
	virtual void update();
	virtual void render();
	virtual void destroy();
	void onKeyPressed(int code);
	void onKeyReleased(int code) {}
	void onKeyTyped(int code) {}
	void onChar(int code, char character) {}
	void onMousePressed(int button) {}
	void onMouseReleased(int button) {}
	void onMouseClicked(int button) {}
	void onMouseMoved(double x, double y, double dx, double dy) {}
	void onMouseDragged(double x, double y, double dx, double dy) {}
	void onMouseEnter() {}
	void onMouseLeave() {}
};

void LightingTest::initialise(Settings* settings) {
	settings->setVideoSamples(16);
	settings->setVideoMaxAnisotropicSamples(16);
	settings->setVideoDeferredRendering(true);
	settings->setDebggingShowInformation(true);
	settings->setDebuggingShowDeferredRenderingBuffers(true);
	wireframe = false;
}

void LightingTest::created() {
	camera = new DebugCamera3D(80, getSettings()->getWindowWidth(), getSettings()->getWindowHeight(), 1, 100);
	camera->setPosition(0, 0, -1);
	camera->toggleFlying();

	TextureParameters::DEFAULT_FILTER = GL_LINEAR_MIPMAP_LINEAR;

	SkyBox* skybox = new SkyBox("C:/UnnamedEngine/skybox", "0.png", "1.png", "2.png", "3.png", "4.png", "5.png", 100);

	camera->setSkyBox(skybox);
	Renderer::addCamera(camera);
	//model = Model::loadModel("C:/UnnamedEngine/Models/mitsuba/", "mitsuba-sphere-blue.obj", "GeometryShader");
	//model = Model::loadModel("C:/UnnamedEngine/Models/mitsuba/", "mitsuba.obj", "GeometryShader");
	//model->position.setY(-1);
	//model = Model::loadModel("C:/UnnamedEngine/Models/head/", "head.obj", "GeometryShader");
	//model = Model::loadModel("C:/UnnamedEngine/Models/", "buddha.obj", "GeometryShader");
	model = Model::loadModel("C:/UnnamedEngine/Models/plane/", "plane.obj", "GeometryShader");
	//model = Model::loadModel("C:/UnnamedEngine/Models/crytek-sponza/", "sponza.obj", "GeometryShader");
	//model->setScale(0.1f, 0.1f, 0.1f);
	model->setPosition(0.0f, -2.5f, 0.0f);
	//model->getMesh(0)->getRenderData()->getMaterial()->setShininess(10.0f);
	//model = Model::loadModel("C:/UnnamedEngine/Models/plane/", "plane.obj", "GeometryShader");
	model2 = Model::loadModel("C:/UnnamedEngine/Models/plane/", "plane2.obj", "GeometryShader");
	//model2 = Model::loadModel("C:/UnnamedEngine/Models/Audi_R8/", "Audi_R8.obj", "GeometryShader");
	model2->setPosition(5.0f, -1.0f, 0.0f);

	scene = new Scene();
	scene->add(model);
	scene->add(model2);
	scene->setLightingEnabled(true);

	if (! scene->isLightingEnabled()) {
		model->setShaderType("Material");
	}

	directionalLight = new DirectionalLight(new BaseLight(Colour::WHITE, 1.0f), Vector3f(0.0, 1.0, -0.3));
	pointLight = new PointLight(new BaseLight(Colour::GREEN, 1.0f), Vector3f(-2.0, 0.2, 0.0), 10.0f);
	spotLight = new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.5), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f);

	//scene->add(directionalLight);
	//scene->add(pointLight);
	//scene->add(spotLight);

	//12 - 214
	randomInit();
	for (unsigned int a = 0; a < 120; a++) {
		float x = randomFloat(14.0f);
		float y = randomFloat(5.0f);
		float z = randomFloat(5.0f);

		PointLight* light = new PointLight(new BaseLight(Colour(randomFloat(), randomFloat(), randomFloat(), 1.0), 1.0f), Attenuation(0.1, 0.1, 0.5), Vector3f(x, y, z), 10.0f);

		scene->add(light);
		pointLights.push_back(light);
	}

	Mouse::lock();
}

void LightingTest::update() {
	camera->update(getDelta());

	if (getWindow()->getKey(GLFW_KEY_RIGHT)) {
		//model->rotation.setY(model->rotation.getY() + 0.05 * getDelta());
		//pointLight->setPosition(pointLight->getPosition() + Vector3f(0.002 * getDelta(), 0.0, 0.0));
		//spotLight->getPointLight()->setPosition(spotLight->getPointLight()->getPosition() + Vector3f(0.001 * getDelta(), 0.0, 0.0));
		model2->position.setX(model2->position.getX() + 0.01 * getDelta());
	} else if (getWindow()->getKey(GLFW_KEY_LEFT)) {
		//pointLight->setPosition(pointLight->getPosition() + Vector3f(-0.002 * getDelta(), 0.0, 0.0));
		//spotLight->getPointLight()->setPosition(spotLight->getPointLight()->getPosition() + Vector3f(-0.001 * getDelta(), 0.0, 0.0));
		model2->position.setX(model2->position.getX() - 0.01 * getDelta());
	}

	if (getWindow()->getKey(GLFW_KEY_R))
		model2->rotation.setY(model2->rotation.getY() + 0.05 * getDelta());

	for (unsigned int a = 0; a < pointLights.size(); a++) {
		if (getWindow()->getKey(GLFW_KEY_PAGE_UP))
			pointLights.at(a)->setPosition(Vector3f(pointLights.at(a)->getPosition().getX(), pointLights.at(a)->getPosition().getY() + 0.0005f * getDelta(), pointLights.at(a)->getPosition().getZ()));
		if (getWindow()->getKey(GLFW_KEY_PAGE_DOWN))
			pointLights.at(a)->setPosition(Vector3f(pointLights.at(a)->getPosition().getX(), pointLights.at(a)->getPosition().getY() - 0.0005f * getDelta(), pointLights.at(a)->getPosition().getZ()));
	}

	model->update();
	model2->update();
}

void LightingTest::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	camera->useView();

	glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE_ARB);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	scene->render(camera->position);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	if (getSettings()->getVideoDeferredRendering()) {
		scene->renderFinal(camera->position);
	}
}

void LightingTest::destroy() {
	//delete &shader;
}

void LightingTest::onKeyPressed(int key) {
	if (key == GLFW_KEY_ESCAPE)
		requestClose();
	else if (key == GLFW_KEY_M) {
		wireframe = ! wireframe;
	} else if (key == GLFW_KEY_F5) {
		getSettings()->setVideoDeferredRendering(! getSettings()->getVideoDeferredRendering());
	} else if (key == GLFW_KEY_F6) {
		scene->setLightingEnabled(! scene->isLightingEnabled());
		if (! scene->isLightingEnabled())
			model->setShaderType("Material");
		else
			model->setShaderType("SpotLight");
	} else if (key == GLFW_KEY_F8) {
		Renderer::initialiseShaders();
	} else if (key == GLFW_KEY_F3)
		Mouse::toggleLock();
}
