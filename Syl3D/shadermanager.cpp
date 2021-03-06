#include "shadermanager.h"

ShaderManager::ShaderManager() {
}

void ShaderManager::initialize() {
	addShader("default", "shaders/defaultvertex.shader", "shaders/defaultfragment.shader");
}

void ShaderManager::addShader(std::string shaderName, std::string vertexShaderPath, std::string fragmentShaderPath) {
	if (_shaderPrograms.find(shaderName) != _shaderPrograms.end()) {
		return;
	}

	_shaderPrograms[shaderName] = _shader.createShaderProgram(vertexShaderPath, fragmentShaderPath);
	_shaderPrograms[shaderName]->use();
	_currentShader = shaderName;
}

void ShaderManager::useShader(std::string shaderName) {
	if (_currentShader == shaderName) {
		return;
	}

	if (_shaderPrograms.find(shaderName) == _shaderPrograms.end()) {
		return;
	}

	_shaderPrograms[shaderName]->use();
	_currentShader = shaderName;
}

std::shared_ptr<ShaderProgram> ShaderManager::shaderByName(std::string shaderName) {
	if (_shaderPrograms.find(shaderName) == _shaderPrograms.end()) {
		return nullptr;
	}

	return _shaderPrograms[shaderName];
}

std::shared_ptr<ShaderProgram> ShaderManager::currentShader() {
	assert(_shaderPrograms.size() > 0);
	return _shaderPrograms[_currentShader];
}