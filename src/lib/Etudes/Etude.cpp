#include <string>

#include <Util/Logging.hpp>

#include "Etude.hpp"

namespace etudes {
    using logging::LogLevel;

    void Etude::draw() {
        // logging::log(LogLevel::excessive,
        //              "drawing number of elements: "s +
        //              std::to_string(elements.size()));

        for(auto &element : elements) {
            element->draw();
        }
    }

    void Etude::addElement(std::unique_ptr<Element> element) {
        elements.push_back(std::move(element));
    }

}
