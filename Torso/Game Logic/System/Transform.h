#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using namespace std;

class Transform {
public:
	Transform(glm::vec3 postion = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	Transform* Parent = NULL;
	vector<Transform*> Children;
	void SetParent(Transform* parent);
	
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);
	void Translate(float x, float y, float z); 
	void Rotate(float x, float y, float z);
};
