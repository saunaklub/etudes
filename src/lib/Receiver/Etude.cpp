#include <string>

#include <Utility/Logging.hpp>

#include "Etude.hpp"

namespace etudes {

    using logging::LogLevel;

    void Etude::registerInputs() {
        for(auto &element : elements) {
            element.second->registerInputs();
        }
    }

    void Etude::draw() {
        for(auto &element : elements) {
            element.second->draw();
        }
    }

    void Etude::addElement(std::string name,
                           std::unique_ptr<Element> element) {
        elements[name] = std::move(element);
    }

}
