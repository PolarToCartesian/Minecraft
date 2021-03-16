#pragma once

#include <common/Header.hpp>

#include <client/Window.hpp>

namespace mc {

    class Client {
    private:
        Window m_window;

    public:
        Client() noexcept;

        void Run() noexcept;
    }; // class Client

    void InitializeDependencies();

    void TerminateDependencies();

}; // namespace mc