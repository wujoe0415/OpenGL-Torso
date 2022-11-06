#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Torso.h"
#include "System/Window.h"
#include "System/Resource_Manager.h"
#include <glm/glm.hpp>
#include "System/Renderer.h"
using namespace std;

class Game{
private:
	Window* window;
	float totalTime;
	KeyInput* keyinputs;
	Renderer* renderer;
	Torso* torso;

public:
	Game();
	void Draw();
	void GameLoop();
	void InitGame();
};