#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Texture.h"
#include "Shader.h"
#include <System/Sprite_Renderer.h>
#include "System/Resource_Manager.h"

class SphereRenderer {
public:
	SphereRenderer(const char* textureName, const char* shaderName);
	void ChangeTexture(char* newTexture);
	void ChangeShader(char* newShader);
	void Render(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 color);
	void Render(glm::mat4 model, glm::vec3 color);
	void InitRenderData();
	Texture2D texture;
	Shader shader;
private:
	unsigned int VAO;
};