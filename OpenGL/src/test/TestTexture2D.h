#pragma once
#include "Test.h"
#include "glm/glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"

namespace test {


	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertextBuffer> m_VertextBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		
		glm::mat4 m_Proj;
		glm::mat4 m_View;

		glm::vec3 m_TranslationFirst;
		glm::vec3 m_TranslationSecond;

	};
}