#pragma once

#include <common/Header.hpp>

#include <client/Window.hpp>

namespace mc {

    class Client {
    private:
        std::unique_ptr<Window> m_pWindow;

    public:
        Client() noexcept;

        void Run() noexcept;
    }; // class Client

    void GLFWErrorCallback(int, const char*);

    void InitializeDependencies();

    void TerminateDependencies();

}; // namespace mc