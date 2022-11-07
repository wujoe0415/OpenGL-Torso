#include "SphereRenderer.h"
#include "Window.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <vector>

SphereRenderer::SphereRenderer(const char* textureName,const char* shaderName) {
	texture = ResourceManager::GetTexture(textureName);
	shader = ResourceManager::GetShader(shaderName);
	InitRenderData();
}
void SphereRenderer::ChangeShader(char* shaderName) {
	shader = ResourceManager::GetShader(shaderName);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);
	InitRenderData();
}
void SphereRenderer::ChangeTexture(char* textureName) {
	texture = ResourceManager::GetTexture(textureName);
}
void SphereRenderer::InitRenderData() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	std::vector<GLfloat> vertices;
	int lats  = 40,longs = 40;
	int indicator = 0;
	for (int i = 0; i <= lats; i++) {
		double lat0 = glm::pi<double>() * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = glm::pi<double>() * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		for (int j = 0; j <= longs; j++) {
			double lng = 2 * glm::pi<double>() * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			vertices.push_back(x * zr0);
			vertices.push_back(y * zr0);
			vertices.push_back(z0);
			indicator++;

			vertices.push_back(x * zr1);
			vertices.push_back(y * zr1);
			vertices.push_back(z1);
			indicator++;
		}
	}
	
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void SphereRenderer::Render(glm::mat4 pmodel, glm::vec3 color) {
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->shader.Use();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	shader.SetMatrix4("view", view);

	glm::mat4 model = pmodel;
	//std::cout << glm::to_string(model) << std::endl;
	shader.SetMatrix4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void SphereRenderer::Render(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec3 color) {
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	this->shader.Use();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Window::getInstance().getWindowWidth() / (float)Window::getInstance().getWindowHeight(), 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	shader.SetMatrix4("view", view);

	glm::mat4 model = glm::mat4(1.0f);

	//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back
	
	model = glm::translate(model, position);

	const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.x),
		glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.y),
		glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
		glm::radians(rotation.z),
		glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotateMatrix = transformX * transformY *  transformZ;

	model *= rotateMatrix;

	model = glm::scale(model, size); // last scale

	//std::cout << glm::to_string(model) << std::endl;
	
	shader.SetMatrix4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}