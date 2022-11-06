#include "GameObject.h"

GameObject::GameObject(){
	transform = new Transform();
}
void GameObject::Render(Renderer* renderer) {
	renderer->Render(transform->GetGlobalPosition(), transform->GetGlobalRotation(), transform->GetGlobalScale(), glm::vec3(1, 1, 1));
	//renderer->Render(transform->GetModelMatrix(), glm::vec3(1, 1, 1));
}