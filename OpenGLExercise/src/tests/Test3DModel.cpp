#include "Test3DModel.h"

#include "Renderer.h"

#include <imgui/imgui.h>
#include <glm/gtx/transform.hpp>

#include "commons/vboindexer.hpp"
#include "commons/TextureLoad.h"

namespace test {
	Test3DModel::Test3DModel(GLFWwindow* window) 
		: Test(window)
		, m_Controls{new Controls(window)}
		, m_LightPower(70.0f)
		, m_LightPosition{ 4.0f, 4.0f, 4.0f }
		, m_LightColor{ 1.0f, 1.0f, 1.0f}
	{
		OBJModel model{ loadOBJ("res/models/suzanne.obj") };
		modelIndexed = indexModelVBO(model);

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

		m_Shader = new Shader("res/shaders/model3DVertex.glsl", "res/shaders/model3DFragment.glsl");

		texture = loadDDS("res/textures/uvmap.DDS");
	}
	Test3DModel::~Test3DModel()
	{
		m_Shader->Unbind();
		ib->Unbind();
		va->Unbind();
		vb->Unbind(); uvb->Unbind(); norb->Unbind();

		delete vb;
		delete uvb;
		delete norb;

		delete layout_vb;
		delete layout_uv;
		delete layout_nor;
		delete va;
		delete ib;
		delete m_Shader;
		glDeleteTextures(1, &texture);

	}
	void Test3DModel::OnUpdate(float deltaTime)
	{
	}
	void Test3DModel::OnRender()
	{
		Renderer::Clear();

		glm::mat4 Model = m_Controls->getModelMatrix();
		Model = glm::rotate(Model, (float)glfwGetTime() * m_RotateSpeed, glm::vec3(1, 1, 1));
		//glm::mat4 View = m_Controls->getViewMatrix();
		glm::mat4 View = glm::lookAt(
			glm::vec3(0, 0, 4), // Camera is at (4,3,-3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		glm::mat4 Projection = m_Controls->getProjectionMatrix();
		glm::mat3 ModelView3x3Matrix = glm::mat3(View * Model);
		glm::mat4 MVP = Projection * View * Model;

		m_Shader->SetUniformMat4("MVP", MVP);
		m_Shader->SetUniformMat4("V", View);
		m_Shader->SetUniformMat4("M", Model);

		m_Shader->SetUniform1f("materialGlow", m_MaterialGlow);
		m_Shader->SetUniform1f("lightPower", m_LightPower);
		m_Shader->SetUniform3f("lightPosition_worldspace", m_LightPosition[0], m_LightPosition[1], m_LightPosition[2]);
		m_Shader->SetUniform3f("lightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2]);

		GLuint tectureSampler = m_Shader->GetUniformLocation("myTextureSampler");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
		glUniform1i(tectureSampler, 0);
		
		Renderer::Draw(*va, *ib, *m_Shader);
	
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Test3DModel::OnImGuiRender()
	{
		ImGui::SliderFloat("Rotate Speed", &m_RotateSpeed, 0.0f, 5.0f);
		ImGui::SliderFloat("Material Glow", &m_MaterialGlow, 0.0f, 200.0f);
		ImGui::SliderFloat("Light Power", &m_LightPower, 0.0f, 500.0f);
		ImGui::SliderFloat3("Light Position", m_LightPosition, -4.0f, 4.0f);
		ImGui::ColorEdit3("Light Color", m_LightColor);
	}
}