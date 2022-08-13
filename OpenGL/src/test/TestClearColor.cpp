#include "TestClearColor.h"

#include <GL/glew.h>
#include "imgui/imgui.h"

#include "Renderer.h"

namespace test {

	TestClearColor::TestClearColor()
		: m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.f }
	{
	}

	TestClearColor::~TestClearColor()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{	
	}

	void TestClearColor::OnRender()
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}

}