#pragma once
#include "System/GameObject.h"
#include <vector>
#include <map>
#include "System/KeyInput.h"
#include "System/Renderer.h"
#include "System/SphereRenderer.h";
using namespace std;

class Torso : public GameObject{
public:
	Torso();
	GameObject* cube;
	GameObject* cube2;
	GameObject* gameObjects;
	GameObject* joints;
	map<string, int> mapping = { {"Torso", 0},{"Head", 1},{"Upper left arm", 2},{"Lower left arm", 3},
								 {"Upper right arm", 4},{"Lower right arm", 5},{"Upper left leg", 6},
								 {"Lower left leg", 7},{"Upper right leg", 8},{"Lower right leg", 9}, 
								 {"Body", 10} };
	glm::vec3 jointpositions[11] = {
		glm::vec3(0,0,0),
		glm::vec3(0,0.6,0),
		glm::vec3(-0.25,0.6,0),
		glm::vec3(-0.72,0.6,0),
		glm::vec3(0.25,0.6,0),
		glm::vec3(0.72,0.6,0),
		glm::vec3(-0.17,-0.1,0),
		glm::vec3(-0.17,-0.35,0),
		glm::vec3(0.17,-0.1,0),
		glm::vec3(0.17,-0.35,0),
		glm::vec3(0,0.3,0),
	};
	glm::vec3 partpositions[11] = {
		glm::vec3(0,0,0),
		glm::vec3(0,0.8,0),
		glm::vec3(-0.5,0.6,0),
		glm::vec3(-0.85,0.6,0),
		glm::vec3(0.5,0.6,0),
		glm::vec3(0.85,0.6,0),
		glm::vec3(-0.17,-0.2,0),
		glm::vec3(-0.17,-0.58,0),
		glm::vec3(0.17,-0.2,0),
		glm::vec3(0.17,-0.58,0),
		glm::vec3(0,0.3,0),
	};
	glm::vec3 partscales[11] = {
		glm::vec3(1,1,1),
		glm::vec3(0.25,0.25,0.25),
		glm::vec3(0.4,0.15,0.15),
		glm::vec3(0.3,0.1,0.15),
		glm::vec3(0.4,0.15,0.15),
		glm::vec3(0.3,0.1,0.15),
		glm::vec3(0.2,0.45,0.15),
		glm::vec3(0.1,0.3,0.15),
		glm::vec3(0.2,0.45,0.15),
		glm::vec3(0.1,0.3,0.15),
		glm::vec3(0.6,0.8,0.3)
	};
	void RotateJoint(GameObject* part, float angle,glm::vec3 direction);
	void ControlPart(string partName, glm::vec3 axis);
	void Draw(Renderer*);
	void DrawJoint(SphereRenderer*);
	void InputHandler();
private:
	KeyInput* Input;
	vector<int> inputList;
	void InputCreater();
};
