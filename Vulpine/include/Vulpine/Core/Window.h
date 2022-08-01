#ifndef __VP_WINDOW_H__
#define __VP_WINDOW_H__

#include <sstream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


namespace Vulpine
{
	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string &title = "Vulpine App",
						 uint32_t width = 1600,
						 uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};
	class Window
	{
	public:
		Window(const WindowProperties &props);
		virtual ~Window();

		virtual void Update(float deltaTime);

		unsigned int GetWidth() const { return m_Props.Width; }
		unsigned int GetHeight() const { return m_Props.Height; }

		virtual GLFWwindow* GetWindow() const { return m_Window; }

		bool shouldClose() { return glfwWindowShouldClose(m_Window); }
		VkExtent2D getExtent() { return { static_cast<uint32_t>(m_Props.Width), static_cast<uint32_t>(m_Props.Height) }; }
		bool wasWindowResized() { return m_FrameBufferResized; }
		void resetWindowResizedFlag() { m_FrameBufferResized = false; }
		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		void Init(const WindowProperties &props);
		void Cleanup();
		
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		bool m_FrameBufferResized = false;
	private:
		WindowProperties m_Props;
		GLFWwindow *m_Window;
	};
}

#endif