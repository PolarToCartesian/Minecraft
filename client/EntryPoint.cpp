#include <client/Client.hpp>

int main(int argc, char** argv) {
    mc::InitializeDependencies();
    
    mc::Client client;

    client.Run();

    mc::TerminateDependencies();
}