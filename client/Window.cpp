#include <client/Window.hpp>

namespace mc {

    Window::Window(const char* const title, const mc::u32 width, const mc::u32 height, mc::Image2Du8& icon) noexcept {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,  GLFW_FALSE);

        this->m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        ASSERT(this->m_handle != NULL, "Failed to create a window");

        GLFWimage glfwIcon;
        glfwIcon.width  = icon.GetWidth();
        glfwIcon.height = icon.GetHeight();
        glfwIcon.pixels = const_cast<mc::u8*>(reinterpret_cast<const mc::u8*>(icon.Data()));

        glfwSetWindowIcon(this->m_handle, 1, &glfwIcon);
    }

    void Window::Update() noexcept {
        if (glfwWindowShouldClose(this->m_handle))
            this->Destroy();

        glfwPollEvents();
    }

}; // namespace mc