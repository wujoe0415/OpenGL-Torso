#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
using namespace std;

class Transform {
public:
	Transform(glm::vec3 postion = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	Transform* Parent;
	vector<Transform*> Children;
	void SetParent(Transform* parent);
	
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);
	void Translate(float x, float y, float z); 
	void Rotate(float x, float y, float z);
	glm::vec3 RotatePivot(float x, float y, float z, glm::vec3 pivot);
	glm::vec3 GetGlobalPosition();
	glm::vec3 GetGlobalRotation();
	glm::vec3 GetGlobalScale();
	void UpdateLocalData();
public:
	glm::vec3 localPosition;
	glm::vec3 localRotation;
	glm::vec3 localScale;
	glm::mat4 modelMatrix;
};
