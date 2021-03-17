#include <client/Client.hpp>
namespace mc {
    
    Client::Client() noexcept
    {
        bool bError;
        Image2Du8 icon("res/icon.png", mc::Image2DFileType::PNG, bError);
        ASSERT(bError == false, "Failed To Load The Window's Icon");

        this->m_pWindow = std::make_unique<mc::Window>("Minecraft Client", 1920, 1080, icon);
        ASSERT(this->m_pWindow->Exists(), "Window Creation Failed");
    }

    void Client::Run() noexcept {
        while (this->m_pWindow->Exists()) {
            this->m_pWindow->Update();
        }
    }

    void GLFWErrorCallback(int, const char* msg) {
        REPORT_ERROR << msg;
    }

    void InitializeDependencies() {
        plog::init(plog::verbose, "log.txt");

        REPORT_DEBUG << InitializeDependencies << '\n';

        glfwSetErrorCallback(mc::GLFWErrorCallback);

        ASSERT(glfwInit() == GLFW_TRUE, "Failed to Initialize GLFW");
    }

    void TerminateDependencies() {
        glfwTerminate();
    }

}; // namespace mc