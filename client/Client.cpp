#include <client/Client.hpp>
namespace mc {
    
    Client::Client() noexcept
        : m_window("Minecraft Client", 1920, 1080)
    {
        
    }

    void Client::Run() noexcept {
        while (this->m_window.Exists()) {
            this->m_window.Update();
        }
    }

    void InitializeDependencies() {
        plog::init(plog::verbose, "log.txt");

        REPORT_DEBUG << "InitializeDependencies...";

        ASSERT(glfwInit() == GLFW_TRUE, "Failed to Initialize GLFW");
    }

    void TerminateDependencies() {
        REPORT_DEBUG << "TerminateDependencies...";

        glfwTerminate();
    }

}; // namespace mc