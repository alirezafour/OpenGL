#include "Test.h"

#include "imgui/imgui.h"

namespace test {


	TestMenu::TestMenu(Test*& currentTestPtr)
		: m_CurrentTest(currentTestPtr)
	{

	}


	void TestMenu::OnImGuiRender()
	{
		for (auto& each : m_Tests)
		{
			if (ImGui::Button(each.first.c_str()))
			{
				m_CurrentTest = each.second();
			}
		}
	}
}
