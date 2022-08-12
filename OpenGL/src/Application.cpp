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
	window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
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
		/* define buffer to begin with before game loop */

		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, // 0
			 0.5f, -0.5f, 1.0f, 0.0f, // 1
			 0.5f,  0.5f, 1.0f, 1.0f, // 2
			-0.5f,  0.5f, 0.0f, 1.0f  // 3
		};

		uint32_t indices[] = { // index buffer
			0, 1, 2,
			2, 3, 0
		};

		// Enable opengl debug call back
		EnableOpenGLDebug();

		// just for blending enable 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		VertexArray va;
		VertextBuffer vb(positions, 4 * 4 * sizeof(float)); // already binded

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		// using index buffer 
		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.2f, 0.0f, 1.0f, 1.0f);

		// 
		Texture texture("res/textures/CppLogo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		// unbind everything
		va.UnBind();
		vb.UnBind();
		ib.UnBind();
		shader.UnBind();

		Renderer renderer;

		float redColor = 0.0f;
		float increament = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			// render here
			renderer.Clear();

			// bind program
			shader.Bind();
			shader.SetUniform4f("u_Color", redColor, 0.0f, 1.0f, 1.0f); // uniform per draw

			renderer.Draw(va, ib, shader);

			// set r to be interp between 1-0 with 0.05f
			if (redColor > 1.0f)
				increament = -0.05f;
			else if (redColor < 0.0f)
				increament = 0.05f;
	
			redColor += increament;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}