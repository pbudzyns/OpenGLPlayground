#include "Test3DModel.h"

#include "Renderer.h"

#include "commons/vboindexer.hpp"
#include "commons/TextureLoad.h"

namespace test {
	Test3DModel::Test3DModel(GLFWwindow* window) : Test(window), m_Controls{new Controls(window)}
	{
		OBJModel model{ loadOBJ("res/models/suzanne.obj") };
		modelIndexed = indexModelVBO(model);

		//GLuint VertexArrayID;
		//glGenVertexArrays(1, &VertexArrayID);
		//glBindVertexArray(VertexArrayID);

		/*

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, modelIndexed.vertices.size() * sizeof(glm::vec3), &modelIndexed.vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, modelIndexed.uvs.size() * sizeof(glm::vec2), &modelIndexed.uvs[0], GL_STATIC_DRAW);

		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, modelIndexed.normals.size() * sizeof(glm::vec3), &modelIndexed.normals[0], GL_STATIC_DRAW);*/

		/*glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelIndexed.indices.size() * sizeof(unsigned short), &modelIndexed.indices[0], GL_STATIC_DRAW);
		*/

		vb = new VertexBuffer(&modelIndexed.vertices[0], modelIndexed.vertices.size() * sizeof(glm::vec3));
		//vertexbuffer = vb->getId();
		layout_vb = new VertexBufferLayout();
		layout_vb->Push<float>(3);

		uvb = new VertexBuffer(&modelIndexed.uvs[0], modelIndexed.uvs.size() * sizeof(glm::vec2));
		//uvbuffer = uvb->getId();
		layout_uv = new VertexBufferLayout();
		layout_uv->Push<float>(2);

		norb = new VertexBuffer(&modelIndexed.normals[0], modelIndexed.normals.size() * sizeof(glm::vec3));
		//normalbuffer = norb->getId();
		layout_nor = new VertexBufferLayout();
		layout_nor->Push<float>(3);

		va = new VertexArray();
		va->AddBuffer(*vb, *layout_vb);
		va->AddBuffer(*uvb, *layout_uv);
		va->AddBuffer(*norb, *layout_nor);
		
		ib = new IndexBuffer(&modelIndexed.indices[0], (unsigned int)modelIndexed.indices.size());
		/*
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

		m_Shader = new Shader("res/shaders/model3DVertex.glsl", "res/shaders/model3DFragment.glsl");

		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glVertexAttribPointer(
		//	0,                  // attribute
		//	3,                  // size
		//	GL_FLOAT,           // type
		//	GL_FALSE,           // normalized?
		//	0,                  // stride
		//	(void*)0            // array buffer offset
		//);

		////// 2nd attribute buffer : UVs
		//glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		//glVertexAttribPointer(
		//	1,                                // attribute
		//	2,                                // size
		//	GL_FLOAT,                         // type
		//	GL_FALSE,                         // normalized?
		//	0,                                // stride
		//	(void*)0                          // array buffer offset
		//);
		////// 3rd attribute buffer : normals
		//glEnableVertexAttribArray(2);
		//glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		//glVertexAttribPointer(
		//	2,                                // attribute
		//	3,                                // size
		//	GL_FLOAT,                         // type
		//	GL_FALSE,                         // normalized?
		//	0,                                // stride
		//	(void*)0                          // array buffer offset
		//);

		texture = loadDDS("res/textures/uvmap.DDS");
	}
	Test3DModel::~Test3DModel()
	{
		delete vb;
		delete uvb;
		delete norb;

		delete layout_vb;
		delete layout_uv;
		delete layout_nor;

		delete ib;
	}
	void Test3DModel::OnUpdate(float deltaTime)
	{
	}
	void Test3DModel::OnRender()
	{
		Renderer::Clear();

		glm::mat4 Model = m_Controls->getModelMatrix();
		glm::mat4 View = m_Controls->getViewMatrix();
		glm::mat4 Projection = m_Controls->getProjectionMatrix();
		glm::mat3 ModelView3x3Matrix = glm::mat3(View * Model);
		glm::mat4 MVP = Projection * View * Model;

		m_Shader->SetUniformMat4("MVP", MVP);
		m_Shader->SetUniformMat4("V", View);
		m_Shader->SetUniformMat4("M", Model);
		//m_Shader->SetUniformMat3("MV3x3", ModelView3x3Matrix);

		m_Shader->SetUniform1f("lightPower", 50.0f);
		m_Shader->SetUniform3f("lightPosition_worldspace", 4.0f, 4.0f, 4.0f);
		m_Shader->SetUniform3f("lightColor", 0.8f, 0.6f, 0.2f);

		GLuint tectureSampler = m_Shader->GetUniformLocation("myTextureSampler");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
		glUniform1i(tectureSampler, 0);
		/*vb->Bind();
		uvb->Bind();
		norb->Bind();
		Renderer::Draw(*va, *ib, *m_Shader);*/

		// 1rst attribute buffer : vertices
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		//ib->Bind();
		//glBindVertexArray(VertexArrayID);
		Renderer::Draw(*va, *ib, *m_Shader);
		// Draw the triangles !
		//glDrawElements(
		//	GL_TRIANGLES,      // mode
		//	modelIndexed.indices.size(),    // count
		//	GL_UNSIGNED_SHORT,   // type
		//	(void*)0           // element array buffer offset
		//);
	}
	void Test3DModel::OnImGuiRender()
	{
	}
}