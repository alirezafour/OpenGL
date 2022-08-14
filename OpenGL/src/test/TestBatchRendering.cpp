#include "TestBatchRendering.h"

#include <GL/glew.h>
#include "imgui/imgui.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"

namespace test {

	TestBatchRendering::TestBatchRendering()
		: m_Proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f))
		, m_View(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)))
		, m_Translation(200.f, 200.f, 0.f)
	{

		glClearColor(0.f, 0.f, 0.f, 1.f);

		float positions[] = {
			-50.f, -50.f, 0.0f, 0.0f,
			 50.f, -50.f, 1.0f, 0.0f,
			 50.f,  50.f, 1.0f, 1.0f,
			-50.f,  50.f, 0.0f, 1.0f,

			100.f, -50.f, 0.0f, 0.0f,
			200.f, -50.f, 1.0f, 0.0f,
			200.f,  50.f, 1.0f, 1.0f,
			100.f,  50.f, 0.0f, 1.0f
		};

		uint32_t indices[] = { // index buffer
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4
		};

		m_VertextBuffer = std::make_unique<VertextBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertextBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.3f, 0.3f, 0.8f, 1.0f);

	}

	TestBatchRendering::~TestBatchRendering()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		m_Shader->UnBind();
	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{	
	}

	void TestBatchRendering::OnRender()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;

		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), m_Translation);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
// 		{
// 			glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationSecond);
// 			glm::mat4 mvp = m_Proj * m_View * model;
// 			m_Shader->Bind();
// 			m_Shader->SetUniformMat4f("u_MVP", mvp);
// 
// 			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
// 		}
	}

	void TestBatchRendering::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation", &m_Translation.x, 0.f, 960.f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}