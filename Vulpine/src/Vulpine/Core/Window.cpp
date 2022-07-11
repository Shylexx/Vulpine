#include "Vulpine/Core/Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Vulpine
{
	Window::Window(const WindowProperties &props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Cleanup();
	}

	void Window::Init(const WindowProperties &props)
	{
		m_Props.Height = props.Height;
		m_Props.Width = props.Width;
		m_Props.Title = props.Title;

		if (!glfwInit())
		{
			std::cout << "GLFW Init Failed" << std::endl;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);

		if (!m_Window)
		{
			std::cout << "Window Creation Failed" << std::endl;
		}
	}

	void Window::Cleanup()
	{
	}

	void Window::Update(float deltaTime)
	{
		glfwPollEvents();
		// m_Context->SwapBuffers();
	}
}