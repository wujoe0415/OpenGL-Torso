#include "GameObject.h"

GameObject::GameObject(){
	transform = new Transform();
}
void GameObject::Render(Renderer* renderer) {
	renderer->Render(transform->Position, transform->Rotation, transform->Scale, glm::vec3(1, 1, 1));
}