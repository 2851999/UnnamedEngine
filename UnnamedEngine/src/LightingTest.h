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

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

class LightingTest : public Game {
private:
	Model* model2;
	Model* model;
	Shader* shader;
	Camera3D* camera;
	Scene* scene;
	DirectionalLight* directionalLight;
	PointLight* pointLight;
	SpotLight* spotLight;
	bool wireframe;
//	GUIButton* button;
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
	void onMouseMoved(double x, double y, double dx, double dy);
	void onMouseDragged(double x, double y, double dx, double dy) {}
	void onMouseEnter() {}
	void onMouseLeave() {}
};

void LightingTest::initialise(Settings* settings) {
	settings->setVideoSamples(16);
	settings->setVideoMaxAnisotropicSamples(16);
	wireframe = false;
}

void LightingTest::created() {
	camera = new Camera3D(Matrix4f().initPerspective(80, ((float) getSettings()->getWindowWidth()) / ((float) getSettings()->getWindowHeight()), 1, 100));
	camera->setPosition(0, 0, -1);
	camera->update();
	camera->toggleFlying();

	TextureParameters::DEFAULT_FILTER = GL_LINEAR_MIPMAP_LINEAR;

	SkyBox* skybox = new SkyBox("C:/UnnamedEngine/", "skybox0.png", "skybox1.png", "skybox2.png", "skybox3.png", "skybox4.png", "skybox5.png", 100);
	camera->setSkyBox(skybox);
	Renderer::addCamera(camera);

//	model = Model::loadModel("C:/UnnamedEngine/Models/mitsuba/", "mitsuba-sphere-blue.obj");
//	model->position.setY(-1);
	model = Model::loadModel("C:/UnnamedEngine/Models/head/", "head.obj", "SpotLight");
//	model = Model::loadModel("C:/UnnamedEngine/Models/crytek-sponza/", "sponza.obj", "SpotLight");
//	model->setScale(0.1f, 0.1f, 0.1f);
//	model->getMesh(0)->getRenderData()->getMaterial()->setShininess(10.0f);
	model->update();

	scene = new Scene();
	scene->add(model);

	directionalLight = new DirectionalLight(new BaseLight(Colour::WHITE, 1.0f), Vector3f(0.0, 0.0, 1.0));

	pointLight = new PointLight(new BaseLight(Colour::GREEN, 1.0f), Vector3f(-1.5, 0.0, 0.0), 10.0f);

	spotLight = new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f);

	scene->add(directionalLight);
	scene->add(pointLight);
	scene->add(spotLight);
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));
//	scene->add(new SpotLight(new PointLight(new BaseLight(Colour::BLUE, 1.0f), Vector3f(0.0, 0.0, 1.0), 10.0f), Vector3f(0.0, 0.0, -1.0), 0.95f));

	Mouse::lock();
}

void LightingTest::update() {
	if (getWindow()->getKey(GLFW_KEY_W)) {
		camera->moveForward(0.08f);
		camera->update();
	} else if (getWindow()->getKey(GLFW_KEY_S)) {
		camera->moveBackward(0.08f);
		camera->update();
	}
	if (getWindow()->getKey(GLFW_KEY_A)) {
		camera->moveLeft(0.08f);
		camera->update();
	} else if (getWindow()->getKey(GLFW_KEY_D)) {
		camera->moveRight(0.08f);
		camera->update();
	}

	if (getWindow()->getKey(GLFW_KEY_RIGHT)) {
		//model->rotation.setY(model->rotation.getY() + 0.05 * getDelta());
		//pointLight->setPosition(pointLight->getPosition() + Vector3f(0.002 * getDelta(), 0.0, 0.0));
		spotLight->getPointLight()->setPosition(spotLight->getPointLight()->getPosition() + Vector3f(0.001 * getDelta(), 0.0, 0.0));
	} else if (getWindow()->getKey(GLFW_KEY_LEFT)) {
		//pointLight->setPosition(pointLight->getPosition() + Vector3f(-0.002 * getDelta(), 0.0, 0.0));
		spotLight->getPointLight()->setPosition(spotLight->getPointLight()->getPosition() + Vector3f(-0.001 * getDelta(), 0.0, 0.0));
	}

	//model->rotation.setY(model->rotation.getY() + 0.05 * getDelta());
	model->update();
}

void LightingTest::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	camera->useView();

	glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE_ARB);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

//	Renderer::setShader(Renderer::getShader("DirectionalLight"));
//	Shader* shader = Renderer::getShader("");
//	shader->use();
//	shader->setUniform("ModelMatrix", model->getModelMatrix());
//	shader->setUniform("AmbientLight", Colour(0.1f, 0.1f, 0.1f, 1.0f));
//	shader->setUniform("SpecularIntensity", 0.2f);
//	shader->setUniform("EyePosition", camera->getPosition());
//	directionalLight->setUniforms(shader, "");
//	scene->render();
//
//	Renderer::resetShader();

	scene->render(camera->position);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	renderInformation();
}

void LightingTest::destroy() {
	//delete &shader;
}

void LightingTest::onMouseMoved(double x, double y, double dx, double dy) {
	camera->setRotation(camera->getRotation() + Vector3f(dy / 5, dx / 5, 0));
	camera->rotation.setX(clamp(camera->rotation.getX(), -80, 80));
	camera->update();
}

void LightingTest::onKeyPressed(int key) {
	if (key == GLFW_KEY_ESCAPE)
		requestClose();
	else if (key == GLFW_KEY_M) {
		wireframe = ! wireframe;
		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else if (key == GLFW_KEY_F3)
		Mouse::toggleLock();
}
