#include "Etude.hpp"

namespace etudes {

    void Etude::draw() {
        for(auto &element : elements) {
            element->draw();
        }
    }

    void Etude::addElement(std::unique_ptr<Element> element) {
        elements.push_back(std::move(element));
    }

}
