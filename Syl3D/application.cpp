#include "application.h"
#include <iostream>

const int Application::INIT_WINDOW_WIDTH = 800;
const int Application::INIT_WINDOW_HEIGHT = 600;
const char* Application::INIT_WINDOW_TITLE = "Syl3D";

Application::Application() 
	:
	_window(nullptr),
	_inputManager(&_renderer)
{}

bool Application::initialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, "Syl3D", nullptr, nullptr);
	if (_window == nullptr) {
		std::cout << "Could not initialize glfw window\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Faield to initalize glad\n";
		glfwTerminate();
		return false;
	}

	glfwSetWindowUserPointer(_window, this);
	glViewport(0, 0, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
	auto frameBufferFunc = [](GLFWwindow* wind, int w, int h)
	{
		static_cast<Application*>(glfwGetWindowUserPointer(wind))->frameBufferSizeCallback(wind, w, h);
	};

	auto mouseCallbackFunc = [](GLFWwindow* wind, double xpos, double ypos)
	{
		static_cast<Application*>(glfwGetWindowUserPointer(wind))->mouseCallback(wind, xpos, ypos);
	};

	auto scrollCallbackFunc = [](GLFWwindow* wind, double xoffset, double yoffset)
	{
		static_cast<Application*>(glfwGetWindowUserPointer(wind))->scrollCallback(wind, xoffset, yoffset);
	};

	auto keyCallbackFunc = [](GLFWwindow* wind, int key, int scancode, int action, int mods)
	{
		static_cast<Application*>(glfwGetWindowUserPointer(wind))->keyCallback(wind, key, scancode, action, mods);
	};

	glfwSetFramebufferSizeCallback(_window, frameBufferFunc);
	glfwSetCursorPosCallback(_window, mouseCallbackFunc);
	glfwSetScrollCallback(_window, scrollCallbackFunc);
	glfwSetKeyCallback(_window, keyCallbackFunc);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

void Application::run() {
	_renderer.initialize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);

	while (!glfwWindowShouldClose(_window)) {
		_inputManager.processInput(_window);
		_renderer.render();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	_inputManager.mouseCallback(window, xpos, ypos);
}

void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	_inputManager.scrollCallback(window, xoffset, yoffset);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	_inputManager.keyCallback(window, key, scancode, action, mods);
}
