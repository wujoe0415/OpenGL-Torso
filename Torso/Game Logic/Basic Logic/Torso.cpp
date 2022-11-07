#include "Torso.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Torso::Torso() {
	InputCreater();
	cube = new GameObject();
	cube2 = new GameObject();
	gameObjects = new GameObject[11];
	joints = new GameObject[11];
	for (int i = 0; i < 11; i++) {
		gameObjects[i].transform->SetPosition(partpositions[i]);
		gameObjects[i].transform->SetScale(partscales[i]);
	}
	for (int i = 0; i < 11; i++) {
		joints[i].transform->SetPosition(jointpositions[i]);
	}
	// joint inheritence
	joints[3].transform->SetParent(joints[2].transform);
	joints[5].transform->SetParent(joints[4].transform);
	joints[7].transform->SetParent(joints[6].transform);
	joints[9].transform->SetParent(joints[8].transform);
	joints[2].transform->SetParent(joints[10].transform);
	joints[4].transform->SetParent(joints[10].transform);
	joints[6].transform->SetParent(joints[10].transform);
	joints[8].transform->SetParent(joints[10].transform);
	joints[1].transform->SetParent(joints[0].transform);
	joints[10].transform->SetParent(joints[0].transform);
	
	for (int i = 0; i < 11; i++)
		gameObjects[i].transform->SetParent(joints[i].transform);
	/*gameObjects[1].transform->SetParent(gameObjects[0].transform);
	gameObjects[10].transform->SetParent(gameObjects[0].transform);
	
	gameObjects[3].transform->SetParent(gameObjects[2].transform);
	gameObjects[5].transform->SetParent(gameObjects[4].transform);
	gameObjects[7].transform->SetParent(gameObjects[6].transform);
	gameObjects[9].transform->SetParent(gameObjects[8].transform);
	
	gameObjects[2].transform->SetParent(gameObjects[10].transform);
	gameObjects[4].transform->SetParent(gameObjects[10].transform);
	gameObjects[6].transform->SetParent(gameObjects[10].transform);
	gameObjects[8].transform->SetParent(gameObjects[10].transform);*/
	
	/*for (int i = 1; i < 11; i++) {
		std::cout << i<<" " <<glm::to_string(gameObjects[i].transform->GetGlobalPosition()) << std::endl;
	}
	std::cout << std::endl;
	for (int i = 1; i < 11; i++) {
		std::cout << i << " " << glm::to_string(gameObjects[i].transform->GetGlobalScale()) << std::endl;
	}*/

	cube->transform->Translate(0.3, 0, 0);
	cube->transform->SetScale(glm::vec3(0.25,0.25,0.25));
	cube2->transform->Translate(-0.3, 0, 0);
	cube2->transform->SetScale(glm::vec3(0.25,0.25,0.25));
	cube2->transform->SetParent(cube->transform);
	
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

	RotateJoint(&(joints[mapping[partName]]), /*(float)glfwGetTime() * */glm::radians(20.0), axis);
}
void Torso::RotateJoint(GameObject* part, float angle, glm::vec3 direction) {
	part->transform->Rotate(angle * direction.x, angle * direction.y, angle * direction.z);
}
void Torso::DrawJoint(SphereRenderer* renderer) {
	for (int i = 1; i < 10; i++) {
		joints[i].Render(renderer);
	}
}
void Torso::Draw(Renderer* renderer) {
	for (int i = 1; i < 11;i++)
		gameObjects[i].Render(renderer);
	//std::cout << glm::to_string(joints[3].transform->GetGlobalPosition())<<std::endl;
	//gameObjects[2].Render(renderer);
	//gameObjects[3].Render(renderer);
	//cube->transform->Translate(0.01f, 0, 0);
	/*cube->transform->Rotate(1, 0, 1);
	std::cout << glm::to_string(cube2->transform->GetGlobalPosition())<<std::endl;
	cube->Render(renderer);
	cube2->Render(renderer);*/
}