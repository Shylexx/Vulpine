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
		//Use For Vulkan
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// Use for OpenGL
		/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);*/

		m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), nullptr, nullptr);

		if (!m_Window)
		{
			std::cout << "Window Creation Failed" << std::endl;
		}

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);

	}

	void Window::Cleanup()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update(float deltaTime)
	{
		//glfwPollEvents();
		// m_Context->SwapBuffers();
	}

	void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, m_Window, nullptr, surface) != VK_SUCCESS ) {
			throw std::runtime_error("Failed to Create Window Surface!");
		}
	}

	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto vpwindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		vpwindow->m_FrameBufferResized = true;
		vpwindow->m_Props.Width = width;
		vpwindow->m_Props.Height = height;

	}
}
