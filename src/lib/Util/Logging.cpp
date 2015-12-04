#include <iostream>

#include <Util/Logging.hpp>

namespace etudes {
    using std::string;
    using std::cout;
    using std::cerr;
    using std::endl;
    
    void log(LogLevel level, std::string message) {
        switch(level) {
        case error:
            cerr << string("ERROR: ") + message << endl;
            break;
        case warning:
            cerr << string("WARNING: ") + message << endl;
            break;
        case info:
            cerr << string("INFO: ") + message << endl;
            break;
        case debug:
            cerr << string("DEBUG: ") + message << endl;
            break;
        }
    }
}
