#include "Torso.h"
#include <iostream>

Torso::Torso() {
	InputCreater();
	cube = new GameObject();
	gameObjects = new GameObject[11];
	for (int i = 0; i < 11; i++) {
		gameObjects[i].transform->SetPosition(partpositions[i]);
		gameObjects[i].transform->SetScale(partscales[i]);
	}
	gameObjects[1].transform->SetParent(gameObjects[0].transform);
	gameObjects[3].transform->SetParent(gameObjects[2].transform);
	gameObjects[5].transform->SetParent(gameObjects[4].transform);
	gameObjects[7].transform->SetParent(gameObjects[6].transform);
	gameObjects[9].transform->SetParent(gameObjects[8].transform);
	gameObjects[10].transform->SetParent(gameObjects[0].transform);
	gameObjects[2].transform->SetParent(gameObjects[10].transform);
	gameObjects[4].transform->SetParent(gameObjects[10].transform);
	gameObjects[6].transform->SetParent(gameObjects[10].transform);
	gameObjects[8].transform->SetParent(gameObjects[10].transform);
}
void Torso::InputCreater() {
	inputList.push_back(GLFW_KEY_0);
	inputList.push_back(GLFW_KEY_1);
	inputList.push_back(GLFW_KEY_2);
	inputList.push_back(GLFW_KEY_3);
	inputList.push_back(GLFW_KEY_4);
	inputList.push_back(GLFW_KEY_5);
	inputList.push_back(GLFW_KEY_6);
	inputList.push_back(GLFW_KEY_7);
	inputList.push_back(GLFW_KEY_8);
	inputList.push_back(GLFW_KEY_9);

	inputList.push_back(GLFW_KEY_X);
	inputList.push_back(GLFW_KEY_Y);
	inputList.push_back(GLFW_KEY_Z);

	Input = new KeyInput(inputList);
}
void Torso::InputHandler() {
	glm::vec3 axis = glm::vec3(0.0);
	if (Input->getIsKeyDown(GLFW_KEY_X))
		axis += glm::vec3(1, 0, 0);
	if (Input->getIsKeyDown(GLFW_KEY_Y))
		axis += glm::vec3(0, 1, 0);
	if (Input->getIsKeyDown(GLFW_KEY_Z))
		axis += glm::vec3(0, 0, 1);

	string part = "";
	if (Input->getIsKeyDown(GLFW_KEY_1))
		part = "Head";
	else if (Input->getIsKeyDown(GLFW_KEY_2))
		part = "Upper left arm";
	else if (Input->getIsKeyDown(GLFW_KEY_3))
		part = "Lower left arm";
	else if (Input->getIsKeyDown(GLFW_KEY_4))
		part = "Upper right arm";
	else if (Input->getIsKeyDown(GLFW_KEY_5))
		part = "Lower right arm";
	else if (Input->getIsKeyDown(GLFW_KEY_6))
		part = "Upper left leg";
	else if (Input->getIsKeyDown(GLFW_KEY_7))
		part = "Lower left leg";
	else if (Input->getIsKeyDown(GLFW_KEY_8))
		part = "Upper right leg";
	else if (Input->getIsKeyDown(GLFW_KEY_9))
		part = "Lower right leg";
	ControlPart(part, axis);
}
void Torso::ControlPart(string partName, glm::vec3 axis) {
	if (partName == "" || axis == glm::vec3(0.0))
		return;

	RotateJoint(&(gameObjects[mapping[partName]]), (float)glfwGetTime() * glm::radians(5.0), axis);
}
void Torso::RotateJoint(GameObject* part, float angle, glm::vec3 direction) {
	part->transform->Rotate(angle * direction.x, angle * direction.y, angle * direction.z);
}
void Torso::Draw(Renderer* renderer) {
	for (int i = 0; i < 11;i++)
		gameObjects[i].Render(renderer);
	//cube->Render(renderer);
	
}