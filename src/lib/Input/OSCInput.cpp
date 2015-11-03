#include <string>
#include <iostream>

#include "OSCInput.hpp"

namespace {
    void error(int num, const char *msg, const char *path) {
        std::cerr << "liblo error " << num
                  << "at " << path
                  << ": " << msg
                  << std::endl;
    }

    int float_handler(const char *path, const char *types, lo_arg ** argv,
                        int argc, void *data, void *user_data) {

        std::cout << "path: " << path << std::endl;
        for(int i = 0; i < argc; ++i) {
            std::cout << "arg " << i
                      << ": " << argv[i]->f
                      << std::endl;
        }
        std::cout << std::endl;

        return 0;
    }

}

namespace etudes {
    
    OSCInput::OSCInput(int iPort) :
        m_iPort(iPort) {
    }

    OSCInput::~OSCInput() {
    }
    
    bool OSCInput::doStart() {
        m_oscServer = lo_server_thread_new(
            std::to_string(m_iPort).c_str(), error);

        lo_server_thread_add_method(
            m_oscServer, NULL, "f",
            float_handler, this);

	return lo_server_thread_start(m_oscServer) == 0;
    }

    void OSCInput::doStop() {
    }

    void OSCInput::update() {
    }
}
