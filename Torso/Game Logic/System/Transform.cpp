#include "Transform.h"

Transform::Transform(glm::vec3 postion, glm::vec3 rotation, glm::vec3 scale) {
	Position = postion;
	Rotation = rotation;
	Scale = scale;
}
void Transform::SetParent(Transform* parent) {
	parent->Children.push_back(this);
}
void Transform::SetPosition(glm::vec3 position) {
	glm::vec3 offset = Position - position;
	this->Position = position;
	for (auto child : Children) {
		child->Translate(offset.x, offset.y, offset.z);
	}
}
void Transform::SetRotation(glm::vec3 rotation) {
	glm::vec3 offset = Rotation;
	this->Rotation = rotation;
	for (auto child : Children) {
		child->Rotate(offset.x, offset.y, offset.z);
	}
}
void Transform::SetScale(glm::vec3 scale) {
	glm::vec3 offset = Scale - scale;
	this->Scale = scale;
	for (auto child : Children) {
		child->SetScale(glm::vec3(child->Scale.x * offset.x, child->Scale.y * offset.y, child->Scale.z * offset.z));
	}
}
void Transform::Translate(float x, float y, float z) {
	SetPosition(this->Position + glm::vec3(x, y, z));
}
void Transform::Rotate(float x, float y, float z) {
	SetRotation(Rotation + glm::vec3(x, y, z));
}