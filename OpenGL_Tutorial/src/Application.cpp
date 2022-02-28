#include <GL/glew.h>
#include <glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Cube.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(540, 540, "OpenGL Tutorial", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	{
		Cube cube;

		VertexArray va;
		VertexBuffer vb(cube.positions, 8 * 3 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(cube.indicies, 48);

		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 1.0f, 0.5f, 0.5f, 1.0f);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		glm::vec3 translation(0.0, 0.0, 0.0);
		float x_rotation_angle = 0;
		float y_rotation_angle = 0;
		float z_rotation_angle = 0;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, translation);
				model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0, 0.0, 0.0));
				model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0, 1.0, 0.0));
				model = glm::rotate(model, z_rotation_angle, glm::vec3(0.0, 0.0, 1.0));

				glm::mat4 mvp = proj * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}

			{
				ImGui::SliderFloat2("TranslationA", &translation.x, -0.5f, 0.5f);
				ImGui::SliderFloat("X rotation angle", &x_rotation_angle, 0.0f, glm::two_pi<float>());
				ImGui::SliderFloat("Y rotation angle", &y_rotation_angle, 0.0f, glm::two_pi<float>());
				ImGui::SliderFloat("Z rotation angle", &z_rotation_angle, 0.0f, glm::two_pi<float>());
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}