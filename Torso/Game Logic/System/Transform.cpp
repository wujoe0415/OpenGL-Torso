#include "Transform.h"

Transform::Transform(glm::vec3 postion, glm::vec3 rotation, glm::vec3 scale) {
	localPosition = postion;
	localRotation = rotation;
	localScale = scale;
	Parent = NULL;
}
glm::mat4 Transform::GetModelMatrix() {
	if (Parent == NULL)
		return GetLocalModelMatrix();
	else
		return GetLocalModelMatrix() * Parent->GetLocalModelMatrix();
}
glm::mat4 Transform::GetLocalModelMatrix()
{
	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
		glm::radians(localRotation.x),
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
		glm::radians(localRotation.y),
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
		glm::radians(localRotation.z),
		glm::vec3(0.0f, 0.0f, 1.0f));

	// Y * X * Z
	const glm::mat4 roationMatrix = transformY * transformX * transformZ;

	// translation * rotation * scale (also know as TRS matrix)
	return glm::translate(glm::mat4(1.0f), localPosition) *
		roationMatrix *	glm::scale(glm::mat4(1.0f), localScale);
}
void Transform::SetParent(Transform* parent) {
	if (parent != NULL)
	{
		for (int i = 0; i < parent->Children.size(); i++)
		{
			if (parent->Children[i] == this)
			{
				parent->Children.erase(parent->Children.begin() + i);
				localPosition += parent->GetGlobalPosition();
				localRotation += parent->GetGlobalRotation();
				localScale *= parent->GetGlobalScale();
				parent = NULL;
				break;
			}
		}
	}
	parent->Children.push_back(this);
	this->Parent = parent;
	UpdateLocalData();
}
void Transform::UpdateLocalData() {
	localPosition -= Parent->GetGlobalPosition();
	localRotation -= Parent->GetGlobalRotation();
	glm::vec3 parentScale = Parent->GetGlobalScale();
	localScale.x = parentScale.x == 0 ? 0 : localScale.x / parentScale.x;
	localScale.y = parentScale.y == 0 ? 0 : localScale.y / parentScale.y;
	localScale.z = parentScale.z == 0 ? 0 : localScale.z / parentScale.z;
}
void Transform::SetPosition(glm::vec3 position) {
	this->localPosition = position;
}
void Transform::SetRotation(glm::vec3 rotation) {
	this->localRotation = rotation;
}
void Transform::SetScale(glm::vec3 scale) {
	this->localScale = scale;
}
void Transform::Translate(float x, float y, float z) {
	SetPosition(this->localPosition + glm::vec3(x, y, z));
}
void Transform::Rotate(float x, float y, float z) {
	SetRotation(localRotation + glm::vec3(x, y, z));
}
glm::vec3 Transform::GetGlobalPosition() {
	if (Parent == NULL)
		return localPosition;
	else
		return Parent->GetGlobalPosition() + localPosition;
}
glm::vec3 Transform::GetGlobalRotation() {
	if (Parent == NULL)
		return localRotation;
	else
		return Parent->GetGlobalRotation() + localPosition;
}
glm::vec3 Transform::GetGlobalScale() {
	if (Parent == NULL)
		return localScale;
	else {
		glm::vec3 parentGlobalScale = Parent->GetGlobalScale();
		return glm::vec3(parentGlobalScale.x * localPosition.x, parentGlobalScale.y * localPosition.y, parentGlobalScale.z * localPosition.z);
	}
}