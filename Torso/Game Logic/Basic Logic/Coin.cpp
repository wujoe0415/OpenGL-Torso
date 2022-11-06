#include "Coin.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Coin::Coin(float width, float height, std::string textureName, std::string shaderName, float moveSpeed, float rotationSpeed) :Entity(width, height, textureName, shaderName) {
	//sprite = new Sprite(width, height, textureName, shaderName);
	x = 100;
	y = 960;
	setPositionX(getPositionX());
	setPositionY(getPositionY());

	angle = 0;
	move_speed = moveSpeed;
	mRotationSpeed = rotationSpeed;
}
void Coin::Draw(SpriteRenderer& Renderer) {
	sprite->Draw(Renderer);
}
void Coin::MoveDown() {
	// move_speed += gravityAcceration
	y -= move_speed;
	setPositionY(getPositionY());

	Rotation();
}
void Coin::MoveUp()
{
	y += move_speed;
	setPositionY(getPositionY());
}
void Coin::Rotation() {
	angle += mRotationSpeed;
	setAngle(angle);
}
//void Coin::Update() {
//
//}