#include "renderer.h"
#include "mesh/rectanglemesh.h"
#include "mesh/coloredtriangle.h"
#include "mesh/texturedrectangle.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <iostream>

Renderer::Renderer() 
	:
	_shaderProgram(-1),
	_texMaterial(&_shaderProgram)
{}

void Renderer::initialize() {
	glEnable(GL_DEPTH_TEST);

	_shaderProgram = _shader.createShaderProgram("shaders/vertex1.shader", "shaders/fragment1.shader");

	math::Vec3 cubePositions[] = {
		math::Vec3(0.0f,  0.0f,  0.0f),
		math::Vec3(2.0f,  5.0f, -15.0f),
		math::Vec3(-1.5f, -2.2f, -2.5f),
		math::Vec3(-3.8f, -2.0f, -12.3f),
		math::Vec3(2.4f, -0.4f, -3.5f),
		math::Vec3(-1.7f,  3.0f, -7.5f),
		math::Vec3(1.3f, -2.0f, -2.5f),
		math::Vec3(1.5f,  2.0f, -2.5f),
		math::Vec3(1.5f,  0.2f, -1.5f),
		math::Vec3(-1.3f,  1.0f, -1.5f)
	};

	for (int i = 0; i < 10; i++) {
		_entities.push_back(std::make_unique<entity::Cube>(cubePositions[i]));
		_entities[i]->scale((float)(i+1) / 5);
	}

	_texMaterial.addTexture("container.jpg");
	_texMaterial.addTexture("awesomeface.png", true, true);
}

void Renderer::render() {
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.use();
	_texMaterial.activateTextures();

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(_freeCamera.zoom()), 800.0f / 600.0f, 0.1f, 100.0f);

	_shaderProgram.setMat4("view", _freeCamera.viewMatrix());
	_shaderProgram.setMat4("projection", projection);

	for (unsigned int i = 0; i < 10; i++) {
		float angle = 20.0f * i;
		angle = (float)glfwGetTime() * angle;
		_entities[i]->rotateTo(glm::radians(angle), math::Vec3(1.0f, 0.3f, 0.5f));
		_shaderProgram.setMat4("model", _entities[i]->modelMatrix());
		_entities[i]->draw();
	}
}