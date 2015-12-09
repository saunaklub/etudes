#include <string>
#include <iostream>

#include <Util/Logging.hpp>

namespace etudes {
    namespace logging {
        using std::string;
        using std::cout;
        using std::cerr;
        using std::endl;

        void log(LogLevel level, std::string message) {
            switch(level) {
            case error:
                cerr << "ERROR: "s + message << endl;
                break;
            case warning:
                cerr << "WARNING: "s + message << endl;
                break;
            case info:
                cerr << "INFO: "s + message << endl;
                break;
            case debug:
                cerr << "DEBUG: "s + message << endl;
                break;
            case excessive:
                cerr << message << endl;
                break;
            }
        }

        std::string to_string(const glm::vec2 &vec) {
            return "("s + std::to_string(vec[0]) +
                ", "s + std::to_string(vec[1]) + ")"s;
        }

        std::string to_string(const glm::vec3 &vec) {
            return "("s + std::to_string(vec[0]) +
                ", "s + std::to_string(vec[1]) +
                ", "s + std::to_string(vec[2]) + ")"s;
        }

    }
}
