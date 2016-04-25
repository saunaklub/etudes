#include <algorithm>
#include <string>

#include <Utility/Logging.hpp>

#include "Etude.hpp"

namespace etudes {

    using std::string;
    using logging::LogLevel;

    void Etude::registerInputs() {
    }

    void Etude::init() {
        for(auto &element : elements) {
            element.second->init();
        }
    }

    void Etude::update() {
        for(auto &element : elements) {
            element.second->update();
        }
    }

    void Etude::draw(const Context &context,
                     const Painter &painter) {
        for(auto &element : elements) {
            element.second->draw(context, painter);
        }
    }

    void Etude::addElement(std::string name,
                           std::unique_ptr<Element> element) {
        elements.push_back(std::make_pair(name, std::move(element)));
    }

    void Etude::dispatchValue(std::string path, vec_t value) {
        auto inputs = getInputs();
        if(std::find(inputs.begin(), inputs.end(), path) != inputs.end()) {
            setValue(path, value);
            return;
        }

        string prefix = splitStringFirst(path);
        auto iter = std::find_if(elements.begin(), elements.end(),
                                 [&](const auto &e)  {
                                     return(e.first == prefix);
                                 });
        if(iter != elements.end()) {
            iter->second->setValue(splitStringRest(path), value);
            return;
        }

        logging::log(
            LogLevel::warning,
            "Etude::dispatchValue: Unable to dispatch message with path: " +
            path);
    }
}
