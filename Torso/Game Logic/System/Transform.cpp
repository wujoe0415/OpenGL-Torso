#include "Transform.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <cmath>

Transform::Transform(glm::vec3 postion, glm::vec3 rotation, glm::vec3 scale) {
	localPosition = postion;
	localRotation = rotation;
	localScale = scale;
	Parent = NULL;
}
void Transform::ComputeModelMatrix() {
	if (Parent == NULL)
		modelMatrix = GetLocalModelMatrix();
	else
		modelMatrix = Parent->GetLocalModelMatrix() * GetLocalModelMatrix();
}
glm::mat4 Transform::GetModelMatrix() {
	//ComputeModelMatrix();
	//return modelMatrix;
	glm::vec3 pivot = glm::vec3(0.0f);
	if (Parent != NULL)
		pivot = Parent->GetGlobalPosition();
	glm::mat4 trans_to_pivot = glm::translate(glm::mat4(1.0f), -pivot);
	glm::mat4 trans_from_pivot = glm::translate(glm::mat4(1.0f), pivot);
	glm::mat4 parent_pivot_rotate = glm::mat4(1.0f);
	if (Parent != NULL) {
		const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
			glm::radians(Parent->localRotation.x),
			glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
			glm::radians(Parent->localRotation.y),
			glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
			glm::radians(Parent->localRotation.z),
			glm::vec3(0.0f, 0.0f, 1.0f));
		parent_pivot_rotate = transformY * transformX * transformZ;
	}

	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
		glm::radians(localRotation.x),
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
		glm::radians(localRotation.y),
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
		glm::radians(localRotation.z),
		glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 localRotation = transformY * transformX * transformZ;
	
	// Y * X * Z
	const glm::mat4 roationMatrix = trans_from_pivot * parent_pivot_rotate * trans_to_pivot *  localRotation;

	glm::vec3 returnPosition = localPosition;
	if (Parent != NULL)
		returnPosition = glm::vec3(0.0f);
	glm::mat4 position = glm::translate(glm::mat4(1.0f), returnPosition);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), GetGlobalScale());
	
	return position * roationMatrix *	scale;
}
void Transform::UpdateSelfAndChildren() {
	//modelMatrix = GetModelMatrix();

	for (Transform* child : Children)
		child->UpdateSelfAndChildren();
}
glm::mat4 Transform::GetLocalModelMatrix()
{
	glm::vec3 pivot = glm::vec3(0.0f);
	if (Parent != NULL)
		pivot = Parent->GetGlobalPosition();
	glm::mat4 trans_to_pivot = glm::translate(glm::mat4(1.0f), -pivot);
	glm::mat4 trans_from_pivot = glm::translate(glm::mat4(1.0f), pivot);
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
	const glm::mat4 roationMatrix = /*trans_from_pivot **/ transformY * transformX * transformZ /** trans_to_pivot*/;
	/*std::cout << "X Rotation : " << glm::to_string(transformX) << std::endl << std::endl;
	std::cout << "Y Rotation : " << glm::to_string(transformY) << std::endl << std::endl;
	std::cout << "Z Rotation : " << glm::to_string(transformZ) << std::endl << std::endl;*/
	//std::cout << "Rotation Matrix : " << glm::to_string(roationMatrix) << std::endl << std::endl;
	// translation * rotation * scale (also know as TRS matrix)
	//std::cout << "Translation : " << glm::to_string(glm::translate(glm::mat4(1.0f), localPosition)) << std::endl << std::endl;
	//std::cout << "Scale : " << glm::to_string(glm::scale(glm::mat4(1.0f), localScale)) << std::endl << std::endl;
	//std::cout << "Rotation X : " << localRotation.x << std::endl;
	/*std::cout << std::endl << glm::to_string(glm::translate(glm::mat4(1.0f), localPosition) *
		roationMatrix *	glm::scale(glm::mat4(1.0f), localScale))<<std::endl;*/
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
				std::cout << "reset parent" << std::endl;
				parent->Children.erase(parent->Children.begin() + i);
				localPosition += parent->GetGlobalPosition();
				localRotation += parent->GetGlobalRotation();
				glm::vec3 parentGlobalScale = parent->GetGlobalScale();
				localScale = glm::vec3(parentGlobalScale.x * localPosition.x, parentGlobalScale.y * localPosition.y, parentGlobalScale.z * localPosition.z);
				parent = NULL;
				break;
			}
		}
	}
	parent->Children.push_back(this);
	//std::cout << "Original : \npoistion : " + glm::to_string(GetGlobalPosition()) << std::endl << "rotation : " + glm::to_string(GetGlobalRotation()) << std::endl << "scale : " + glm::to_string(GetGlobalScale()) << std::endl << std::endl;
	this->Parent = parent;
	UpdateLocalData();
}
void Transform::UpdateLocalData() {
	localPosition -= Parent->GetGlobalPosition();
	//std::cout << "Update to " << glm::to_string(localPosition) << std::endl;
	localRotation -= Parent->GetGlobalRotation();
	glm::vec3 parentScale = Parent->GetGlobalScale();
	//std::cout << "localscale.x : " << localScale.x << ", parentscale.x"<< parentScale.x <<" "<< (float)localScale.x / parentScale.x<< std::endl;
	//std::cout << "localscale.y : " << localScale.y << ", parentscale.y"<< parentScale.y <<" "<< (float)localScale.y / parentScale.y<< std::endl;
	//std::cout << "localscale.z : " << localScale.z << ", parentscale.z" << parentScale.z << " " << (float)localScale.z / parentScale.z << std::endl;
	localScale.x = parentScale.x == 0.0f ? 0.0f : (float)localScale.x / parentScale.x;
	localScale.y = parentScale.y == 0.0f ? 0.0f : (float)localScale.y / parentScale.y;
	localScale.z = parentScale.z == 0.0f ? 0.0f : (float)localScale.z / parentScale.z;
	//std::cout << "\nAfter : \npoistion : " + glm::to_string(GetGlobalPosition()) << std::endl << "rotation : " + glm::to_string(GetGlobalRotation()) << std::endl << "scale : " + glm::to_string(GetGlobalScale()) << std::endl << std::endl;

	//std::cout << "localscale : " << glm::to_string(localScale)<<std::endl;
}
void Transform::SetPosition(glm::vec3 position) {
	if (Parent == NULL)
		this->localPosition = position;
	else
		this->localPosition = position - Parent->GetGlobalPosition();
	UpdateSelfAndChildren();
}
void Transform::SetRotation(glm::vec3 rotation) {
	if (Parent == NULL)
		this->localRotation = rotation;
	else
		this->localRotation = rotation - Parent->GetGlobalRotation();
	UpdateSelfAndChildren();
}
void Transform::SetScale(glm::vec3 scale) {
	if (Parent == NULL)
		this->localScale = scale;
	else
	{
		glm::vec3 parentScale = Parent->GetGlobalScale();
		localScale.x = parentScale.x == 0 ? 0 : (float)scale.x / parentScale.x;
		localScale.y = parentScale.y == 0 ? 0 : (float)scale.y / parentScale.y;
		localScale.z = parentScale.z == 0 ? 0 : (float)scale.z / parentScale.z;
	}
	UpdateSelfAndChildren();
}
void Transform::Translate(float x, float y, float z) {
	this->localPosition += glm::vec3(x, y, z);
	UpdateSelfAndChildren();
}
glm::vec3 Transform::RotatePivot(float x, float y, float z, glm::vec3 pivot) {
	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
		glm::radians(x),
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
		glm::radians(y),
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
		glm::radians(z),
		glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 parent_pivot_rotate = transformX *transformY *  transformZ;
	float radius = glm::distance(localPosition, glm::vec3(0.0f));
	glm::vec3 direction = glm::vec3(parent_pivot_rotate * glm::vec4(localPosition, 1.0f));
	
	/*direction.z = -cos(yaw)*sin(pitch)*sin(roll) - sin(yaw)*cos(roll);
	direction.x = -sin(yaw)*sin(pitch)*sin(roll) + cos(yaw)*cos(roll);
	direction.y = cos(pitch)*sin(roll);*/
	
	glm::vec3 lastposition = pivot + /*radius **/ direction;
	//std::cout << "direction : " << glm::to_string(direction) << std::endl;
	//std::cout << glm::to_string(lastposition)<<std::endl;
	return lastposition;
}
void Transform::Rotate(float x, float y, float z) {
	localRotation += glm::vec3(x, y, z);
	UpdateSelfAndChildren();
}
glm::vec3 Transform::GetGlobalPosition() {
	if (Parent == NULL)
		return localPosition;
	else {
		//std::cout << "Absolute position " << glm::to_string(Parent->GetGlobalPosition() + localPosition) << std::endl;
		return RotatePivot(Parent->GetGlobalRotation().x,Parent->GetGlobalRotation().y,Parent->GetGlobalRotation().z, Parent->GetGlobalPosition());
	}
}
glm::vec3 Transform::GetGlobalRotation() {
	if (Parent == NULL)
		return localRotation;
	else
		return Parent->GetGlobalRotation() + localRotation;
}
glm::vec3 Transform::GetGlobalScale() {
	if (Parent == NULL)
		return localScale;
	else {
		glm::vec3 parentGlobalScale = Parent->GetGlobalScale();
		return glm::vec3(parentGlobalScale.x * localScale.x, parentGlobalScale.y * localScale.y, parentGlobalScale.z * localScale.z);
	}
}