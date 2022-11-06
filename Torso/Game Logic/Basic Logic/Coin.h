#pragma once
#include "Entity.h"

class Coin : public Entity {
public:
	float move_speed;

	Coin(float, float, std::string, std::string, float, float);
	~Coin() {};
	void Draw(SpriteRenderer&);
	void MoveDown();
	void MoveUp();
	void Rotation();
	//virtual void Update();
protected:
	float mRotationSpeed;
};