#include <client/Window.hpp>

namespace mc {

    Window::Window(const char* const title, const mc::u32 width, const mc::u32 height) noexcept {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE,  GLFW_FALSE);

        this->m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        ASSERT(this->m_handle != NULL, "Failed to create a window");
    }

    void Window::Update() noexcept {
        if (glfwWindowShouldClose(this->m_handle))
            this->Destroy();

        glfwPollEvents();
    }

}; // namespace mc