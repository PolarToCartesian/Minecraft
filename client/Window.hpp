#pragma once

#include <common\Image.hpp>
#include <common\Header.hpp>

namespace mc {

	class Window {
	private:
		GLFWwindow* m_handle = nullptr;

	public:
        Window() noexcept = default;

        FORCE_INLINE Window(Window&& win) noexcept
            : m_handle(win.m_handle)
        {
            win.m_handle = nullptr;
        }

        Window(const char* const title, const mc::u32 width, const mc::u32 height, mc::Image2Du8& icon) noexcept;

        FORCE_INLINE bool Exists() const noexcept { return this->m_handle != nullptr; }

        void Update() noexcept;

        GLFWwindow* GetGLFWHandle() const noexcept { return this->m_handle; }

#ifdef _WIN32
        FORCE_INLINE HWND GetNativeHandle() const noexcept { return glfwGetWin32Window(this->m_handle); }
#endif // _WIN32

        FORCE_INLINE void Destroy() noexcept {
            glfwDestroyWindow(this->m_handle);

            this->m_handle = nullptr;
        }

        FORCE_INLINE ~Window() noexcept {
            if (this->m_handle)
                this->Destroy();
        }
	}; // class Window

}; // namespace mc