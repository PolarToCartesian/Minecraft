#pragma once

#include <common/Header.hpp>

#include <client/Window.hpp>
#include <client/Renderer.hpp>

namespace mc {

    class Client {
    private:
        std::unique_ptr<mc::Window>   m_pWindow;
        std::unique_ptr<mc::Renderer> m_pRenderer;

    public:
        Client() noexcept;

        void Run() noexcept;
    }; // class Client

    void GLFWErrorCallback(int, const char*);

    void InitializeDependencies();

    void TerminateDependencies();

}; // namespace mc