#include "Vulpine/Core/Window.h"

namespace Vulpine
{
	Window::Window(const WindowProperties& props) {
		Init(props);
	}

	Window::~Window()
	{
		Cleanup();
	}

	void Window::Init(const WindowProperties& props) {
		m_Props.Height = props.Height;
		m_Props.Width = props.Width;
		m_Props.Title = props.Title;


	}

	void Window::Cleanup() {

	}

	void Window::Update(float deltaTime) {
		glfwPollEvents();
		//m_Context->SwapBuffers();
	}
}