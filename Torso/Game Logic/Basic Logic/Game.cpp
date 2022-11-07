#include "Game.h"
#include <time.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "System/stb_image.h"

Game::Game() {
	window = &Window::getInstance();
	// Inititialize Render Data
	ResourceManager::LoadShader("cube.vert", "cube.frag", nullptr, "standard");
	ResourceManager::LoadTexture("Resources/lightblue.png", false, "lightblue");
	ResourceManager::GetShader("standard").Use().SetInteger("standard", 0);
	sphererenderer = new SphereRenderer("lightblue", "standard");
	renderer = new Renderer("lightblue", "standard");
	InitGame();
} 
void Game::InitGame() {
	torso = new Torso();
	totalTime = 0;
	glfwSetTime(0);
}
void Game::Draw() {
	torso->Draw(renderer);
	//torso->DrawJoint(sphererenderer);
}
void Game::GameLoop() {
	float deltaTime = glfwGetTime() - totalTime;
	totalTime = glfwGetTime();

	torso->InputHandler();
}