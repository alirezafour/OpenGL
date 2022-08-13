#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// set profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "Hello OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	/* Init glew after glfw Context */
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

	// Print opengl version we are using
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Enable opengl debug call back
		EnableOpenGLDebug();

		// just for blending enable 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Renderer renderer;

		const char* glsl_version = "#version 100";

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		test::Test* currentTest = nullptr;
		std::unique_ptr<test::TestMenu> testMenu = std::make_unique<test::TestMenu>(currentTest);
		currentTest = testMenu.get();

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			// render here
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0.f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu.get() && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu.get();
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}