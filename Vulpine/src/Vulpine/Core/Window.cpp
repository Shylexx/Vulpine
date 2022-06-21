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

	}

	void Window::Cleanup() {

	}
}