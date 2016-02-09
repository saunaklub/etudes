#include <string>

#include <Utility/Logging.hpp>

namespace etudes {
    namespace logging {

        LogLevel logLevelMax = LogLevel::excessive;

        std::string to_string(const glm::vec2 &vec) {
            return "("s + std::to_string(vec[0]) +
                ", "s + std::to_string(vec[1]) + ")"s;
        }

        std::string to_string(const glm::vec3 &vec) {
            return "("s + std::to_string(vec[0]) +
                ", "s + std::to_string(vec[1]) +
                ", "s + std::to_string(vec[2]) + ")"s;
        }

        void setLogLevelMax(LogLevel logLevel) {
            logLevelMax = logLevel;
        }
    }
}
