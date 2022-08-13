#include "TestTexture2D.h"

#include <GL/glew.h>
#include "imgui/imgui.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.f, 1.f))
		, m_View(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)))
		, m_TranslationFirst(200.f, 200.f, 0.f), m_TranslationSecond(400.f, 200.f, 0.f)
	{
		float positions[] = {
			-50.f, -50.f, 0.0f, 0.0f, // 0
			 50.f, -50.f, 1.0f, 0.0f, // 1
			 50.f,  50.f, 1.0f, 1.0f, // 2
			-50.f,  50.f, 0.0f, 1.0f  // 3
		};

		uint32_t indices[] = { // index buffer
			0, 1, 2,
			2, 3, 0
		};


		// just for blending enable 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		m_VertextBuffer = std::make_unique<VertextBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertextBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.0f, 1.0f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/CppLogo.png");
		m_Texture->Bind();

		m_Shader->SetUniform1i("u_Texture", 0);

	}

	TestTexture2D::~TestTexture2D()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		m_Shader->UnBind();
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{	
	}

	void TestTexture2D::OnRender()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;

		m_Texture->Bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationFirst);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationSecond);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation first", &m_TranslationFirst.x, 0.f, 960.f);
		ImGui::SliderFloat3("Translation Second", &m_TranslationSecond.x, 0.f, 960.f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}