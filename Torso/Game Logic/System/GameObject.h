#pragma once
#include "Transform.h"
#include "Renderer.h"

class GameObject {
public:
	GameObject();
	Transform* transform;
	void Render(Renderer*);
};