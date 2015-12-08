#include <string>
#include <iostream>

#include <Util/Logging.hpp>

using namespace std::literals::string_literals;

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
            }
        }
    }
}
