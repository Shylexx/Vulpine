#ifndef __VP_WINDOW_H__
#define __VP_WINDOW_H__

#include <sstream>
#include <GLFW/glfw3.h>

namespace Vulpine
{
	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = "Vulpine App",
			uint32_t width = 1600,
			uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};
	class Window
	{
	public:
		Window(const WindowProperties& props);
		virtual ~Window();

		virtual void Update(float deltaTime) = 0;

		unsigned int GetWidth() const { return m_Props.Width; }
		unsigned int GetHeight() const { return m_Props.Height; }

		virtual void* GetWindow() const { return m_Window; }

	private:
		void Init(const WindowProperties& props);
		void Cleanup();
	private:
		WindowProperties m_Props;
		GLFWwindow* m_Window;
	};
}

#endif