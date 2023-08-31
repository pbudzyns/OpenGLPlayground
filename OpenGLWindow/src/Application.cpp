#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#include "commons/Shader.h"
#include "commons/Controls.h"
#include "commons/loadObj.h"
#include "commons/Texture.h"
#include "commons/vboindexer.hpp"
#include "commons/Text2D.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int WIDTH{ 3096 };
	int HEIGHT{ 1900 };

	GLFWwindow* window{ glfwCreateWindow(WIDTH, HEIGHT, "Tutorial 01", nullptr, nullptr) };
	if (!window)
	{
		std::cerr << "Failed to open GLFW Window!" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return 1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);

	GLuint program{ Shader::LoadShader(
		"res/shaders/normalMappingVertex.glsl", 
		"res/shaders/normalMappingFragment.glsl"
	) };

	OBJModel model{ loadOBJ("res/models/cylinder.obj", true) };
	OBJModelIndexed modelIndexed{ indexModelVBO(model) };
	
	//GLuint texture{ loadDDS("res/textures/uvmap.DDS")};
	GLuint DiffuseTexture = loadDDS("res/textures/diffuse.DDS");
	GLuint NormalTexture = loadBMP_custom("res/textures/normal.bmp");
	GLuint SpecularTexture = loadDDS("res/textures/specular.DDS");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, modelIndexed.vertices.size() * sizeof(glm::vec3), &modelIndexed.vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, modelIndexed.uvs.size() * sizeof(glm::vec2), &modelIndexed.uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, modelIndexed.normals.size() * sizeof(glm::vec3), &modelIndexed.normals[0], GL_STATIC_DRAW);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelIndexed.indices.size() * sizeof(unsigned short), &modelIndexed.indices[0], GL_STATIC_DRAW);

	GLuint tangentbuffer;
	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, modelIndexed.tangents.size() * sizeof(glm::vec3), &modelIndexed.tangents[0], GL_STATIC_DRAW);

	GLuint bitangentbuffer;
	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, modelIndexed.bitangents.size() * sizeof(glm::vec3), &modelIndexed.bitangents[0], GL_STATIC_DRAW);


	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat3 ModelView3x3Matrix;
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model;

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(program, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(program, "V");
	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	GLuint ModelView3x3MatrixID = glGetUniformLocation(program, "MV3x3");

	GLuint LightID = glGetUniformLocation(program, "lightPosition_worldspace");
	GLuint TextureID = glGetUniformLocation(program, "myTextureSampler");
	GLuint LightColorID = glGetUniformLocation(program, "lightColor");
	GLuint LightPowerID = glGetUniformLocation(program, "lightPower");

	GLuint DiffuseTextureID = glGetUniformLocation(program, "diffuseTextureSampler");
	GLuint NormalTextureID = glGetUniformLocation(program, "normalTextureSampler");
	GLuint SpecularTextureID = glGetUniformLocation(program, "specularTextureSampler");

	
	glm::vec3 lightPos = glm::vec3(4, 4, 4);
	float radius{ 6.0f }, theta{ 0.0f }, thetaDelta{ 0.05f };
	Controls controls(window);
	Text2D textRenderer("res/textures/Holstein.DDS");

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	std::string message{"0 ms/frame"};
	do {
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
			// printf and reset
			float msPerFrame = 1000.0f / float(nbFrames);
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << msPerFrame << " ms/frame";
			message = ss.str();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		textRenderer.print(message, 10, 500, 60);
		glUseProgram(program);

		Model = controls.getModelMatrix();
		View = controls.getViewMatrix();
		Projection = controls.getProjectionMatrix();
		ModelView3x3Matrix = glm::mat3(View * Model);
		MVP = Projection * View * Model;
		
		/*lightPos.x = radius * cos(theta);
		lightPos.z = radius * sin(theta);
		theta += thetaDelta;*/

		glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(LightColorID, 0.9f, 0.6f, 0.2f);
		glUniform1f(LightPowerID, 70.0f);
		// 
		// Bind our diffuse texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
		// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
		glUniform1i(DiffuseTextureID, 0);

		// Bind our normal texture in Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, NormalTexture);
		// Set our "NormalTextureSampler" sampler to use Texture Unit 1
		glUniform1i(NormalTextureID, 1);

		// Bind our specular texture in Texture Unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, SpecularTexture);
		// Set our "SpecularTextureSampler" sampler to use Texture Unit 2
		glUniform1i(SpecularTextureID, 2);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		// 4th attribute buffer : tangents
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
		glVertexAttribPointer(
			3,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 5th attribute buffer : bitangents
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
		glVertexAttribPointer(
			4,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			modelIndexed.indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		

		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(program);
	glDeleteTextures(1, &DiffuseTexture);
	glDeleteTextures(1, &NormalTexture);
	glDeleteTextures(1, &SpecularTexture);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}