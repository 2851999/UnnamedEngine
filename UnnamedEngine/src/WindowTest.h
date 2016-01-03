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

#include "core/CoreEngine.h"
#include "core/gui/Font.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

class WindowTest : public BaseEngine {
private:
	RenderableObject3D object;
	Model* model2;
	Model* model;
	Shader* shader;
	Camera3D* camera;
	bool wireframe;
//	GUIButton* button;
public:
	virtual ~WindowTest() {}
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

void WindowTest::initialise(Settings* settings) {
	settings->setVideoSamples(16);
	settings->setVideoMaxAnisotropicSamples(16);
	//settings->setWindowDecorated(false);
	//settings->setVideoResolution(VIDEO_RESOLUTION_1080P);
	//settings->setWindowFullscreen(true);
	wireframe = false;
}

void WindowTest::created() {
	logDebug("Hello World!");
	logDebug(getSettings()->getWindowTitle());
	Renderer::initialise();
	//camera = Camera2D(Matrix4f().setOrphographic(0, 1280, 720, 0, -1, 1));
	camera = new Camera3D(Matrix4f().initPerspective(80, 1280.0f / 720.0f, 1, 100));
	camera->setPosition(0, 0, -2);
	camera->update();
	camera->toggleFlying();

	TextureParameters::DEFAULT_FILTER = GL_LINEAR_MIPMAP_LINEAR;

	SkyBox* skybox = new SkyBox("H:/Andor2/", "skybox0.png", "skybox1.png", "skybox2.png", "skybox3.png", "skybox4.png", "skybox5.png", 100);
	camera->setSkyBox(skybox);
	Renderer::addCamera(camera);

	Texture* texture = Texture::loadTexture("H:/Andor2/Tests/Sound/wood2.jpg", TextureParameters().setFilter(GL_LINEAR_MIPMAP_LINEAR), true);
//	object = RenderableObject2D(MeshBuilder::createQuad(100, 100, texture, colours, 2));
//	object.setPosition(200, 200);
	object = RenderableObject3D(MeshBuilder::createCube(1, 1, 1, texture, Colour(1.0f, 1.0f, 1.0f, 1.0f)));
	object.getMesh()->setTexture(texture);
	object.setPosition(2, 0, 0);
	object.update();

//	object.getMesh()->getData()->clearColours();
//	MeshBuilder::addCubeC(object.getMesh()->getData(), Colour::ARRAY_BLUE, 2);
//	object.getMesh()->updateColours();

//	model2 = Model::loadModel("H:/Andor/", "ship.obj");
//	model2->setPosition(3, 2, 0);
//	model2->setScale(0.01f, 0.01f, 0.01f);
//	model2->update();
//	model = Model::loadModel("H:/Storage/Users/Joel/Desktop/To be sorted/", "gingerbreadman.dae");
//	model = Model::loadModel("H:/Andor/", "monkey.obj");
	model = Model::loadModel("C:/UnnamedEngine/Models/", "teapot.obj");
//	model = Model::loadModel("C:/UnnamedEngine/Models/crytek-sponza/", "sponza.obj");
//	model->setScale(0.1f, 0.1f, 0.1f);
	model->update();

//	std::vector<Colour> colours;
//	colours.push_back(Colour::RED);
//	colours.push_back(Colour::GREEN);
//	colours.push_back(Colour::BLUE);
//	button = new GUIButton("Click Me", colours, 100, 20);
//	button->setPosition(100, 400);

	Mouse::lock();
}

void WindowTest::update() {
	//std::cout << glfwGetTime() << std::endl;
	if (getWindow()->getKey(GLFW_KEY_RIGHT)) {
		object.setRotation(object.getRotation() + Vector3f(0.0f, 1.0f, 0.0f));
		object.update();
	} else if (getWindow()->getKey(GLFW_KEY_LEFT)) {
		object.setRotation(object.getRotation() - Vector3f(0.0f, 1.0f, 0.0f));
		object.update();
	}
	if (getWindow()->getKey(GLFW_KEY_UP)) {
		object.setRotation(object.getRotation() - Vector3f(1.0f, 0.0f, 0.0f));
		object.update();
	} else if (getWindow()->getKey(GLFW_KEY_DOWN)) {
		object.setRotation(object.getRotation() + Vector3f(1.0f, 0.0f, 0.0f));
		object.update();
	}

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


//	button->update();
}

void WindowTest::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_DEPTH_TEST);
	camera->useView();
	object.render();

	glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE_ARB);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	model->render();
	//	model2->render();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	renderInformation();

//	button->render();

//	Renderer::removeCamera();
}

void WindowTest::destroy() {
	//delete &shader;
}

void WindowTest::onMouseMoved(double x, double y, double dx, double dy) {
	camera->setRotation(camera->getRotation() + Vector3f(dy / 5, dx / 5, 0));
	camera->rotation.setX(clamp(camera->rotation.getX(), -80, 80));
	camera->update();
}

void WindowTest::onKeyPressed(int key) {
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
