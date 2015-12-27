#include <string>

#include <Util/Logging.hpp>

#include "Etude.hpp"

namespace etudes {

    using logging::LogLevel;

    void Etude::registerInputs() {
        for(auto &element : elements) {
            element->registerInputs();
        }
    }

    void Etude::draw() {
        for(auto &element : elements) {
            element->draw();
        }
    }

    void Etude::addElement(std::unique_ptr<Element> element) {
        elements.push_back(std::move(element));
    }

}
