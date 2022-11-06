//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//
//#include <stdio.h>
//#include "System/Window.h"
//#include <iostream>
//#include "System/KeyInput.h"
//#include "Basic Logic/Game.h"
//#include "System/stb_image.h"
//
//void CloseWindow()
//{
//	glfwSetWindowShouldClose(Window::getInstance().sWindow, GLFW_TRUE);
//}
//void InitRenderData() {
//	
//}
//void DrawCube() {
//	
//}
//int main(void)
//{
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//	
//	Window* window = &Window::getInstance();
//	window->CreateWindow(960, 960);
//	
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	glEnable(GL_BLEND);
//	glEnable(GL_DEPTH_TEST);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	//Game* CoinCatcher = new Game();
//	//CoinCatcher->setGameMode(1);
//
//	vector<int> inputList{ GLFW_KEY_ESCAPE };
//	KeyInput* keyinputs = new KeyInput(inputList);
//	// Initialize Input callback
//	KeyInput::setupKeyInputs(*window);
//
//#pragma region InitRenderData;
//	ResourceManager::LoadShader("cube.vert", "cube.frag", nullptr, "standard");
//	ResourceManager::LoadTexture("Resources/miner.png", true, "player");
//	// build and compile our shader zprogram
//   // ------------------------------------
//	Shader ourShader = ResourceManager::GetShader("standard");
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//	glm::vec3 cubePositions[] = {
//	glm::vec3(0.0f,  0.0f,  0.0f),
//	glm::vec3(2.0f,  5.0f, -15.0f),
//	glm::vec3(-1.5f, -2.2f, -2.5f),
//	glm::vec3(-3.8f, -2.0f, -12.3f),
//	glm::vec3(2.4f, -0.4f, -3.5f),
//	glm::vec3(-1.7f,  3.0f, -7.5f),
//	glm::vec3(1.3f, -2.0f, -2.5f),
//	glm::vec3(1.5f,  2.0f, -2.5f),
//	glm::vec3(1.5f,  0.2f, -1.5f),
//	glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	unsigned int VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// texture coord attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//
//	// load and create a texture 
//	// -------------------------
//	unsigned int texture1, texture2;
//	// texture 1
//	// ---------
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// load image, create texture and generate mipmaps
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	unsigned char *data = stbi_load("Resources/miner.png", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//	// -------------------------------------------------------------------------------------------
//	ourShader.Use();
//	ourShader.SetInteger("standard", 0);
//#pragma endregion InitRenderData;
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window->sWindow))
//	{
//		if (keyinputs->getIsKeyDown(GLFW_KEY_ESCAPE))
//			CloseWindow();
//
//		//CoinCatcher->GameLoop();
//
//		/* Poll for and process events */
//		glfwPollEvents();
//
//		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		/* Swap front and back buffers */
//		
//		//DrawCube();
//		// bind textures on corresponding texture units
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//
//		// activate shader
//		ourShader.Use();
//
//		// create transformations
//		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//		glm::mat4 view = glm::mat4(1.0f);
//		glm::mat4 projection = glm::mat4(1.0f);
//		
//		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f));
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//		projection = glm::perspective(glm::radians(45.0f), (float)window->getWindowWidth() / (float)window->getWindowWidth(), 0.1f, 100.0f);
//		// retrieve the matrix uniform locations
//		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
//		// pass them to the shaders (3 different ways)
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//		ourShader.SetMatrix4("projection", projection);
//
//		// render container
//		glBindVertexArray(VAO);
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			ourShader.SetMatrix4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		//CoinCatcher->Draw();
//		glfwSwapBuffers(window->sWindow);
//	}
//	glfwTerminate();
//	return 0;
//}

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include "System/Window.h"
#include <iostream>
#include "System/KeyInput.h"
#include "Basic Logic/Game.h"
#include "System/stb_image.h"

void CloseWindow()
{
	glfwSetWindowShouldClose(Window::getInstance().sWindow, GLFW_TRUE);
}
int main(void)
{
	/* Initialize the library */
if (!glfwInit())
return -1;

Window* window = &Window::getInstance();
window->CreateWindow(960, 960);

if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
}
glEnable(GL_BLEND);
glEnable(GL_DEPTH_TEST);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
Game* torsoSimulator = new Game();

//Game* CoinCatcher = new Game();
//CoinCatcher->setGameMode(1);

vector<int> inputList{ GLFW_KEY_ESCAPE };
KeyInput* keyinputs = new KeyInput(inputList);
// Initialize Input callback*/
KeyInput::setupKeyInputs(*window);

/* Loop until the user closes the window*/
while (!glfwWindowShouldClose(window->sWindow))
{
	if (keyinputs->getIsKeyDown(GLFW_KEY_ESCAPE))
		CloseWindow();

	torsoSimulator->GameLoop();

	/* Poll for and process events*/
	glfwPollEvents();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	torsoSimulator->Draw();

	/* Swap front and back buffers*/
	glfwSwapBuffers(window->sWindow);
}
glfwTerminate();
return 0;
}
