#include <functional>

#include <yaml-cpp/yaml.h>

#include <Utility/Utility.hpp>

#include <Elements/Element.hpp>
#include <Elements/ElementLine.hpp>

#include "ElementFactory.hpp"

namespace etudes {

    using YAML::Node;

    std::map<std::string, ElementFactory::creation_t>
    ElementFactory::creationMap = {
        {"line", ElementFactory::makeLineElement}
    };

    std::unique_ptr<Element>
    ElementFactory::makeElement(const Node &node) {
        std::unique_ptr<Element> product;

        std::string type = node["type"].as<std::string>();
        return creationMap[type](node);
    }

    std::unique_ptr<Element>
    ElementFactory::makeLineElement(const Node &node) {
        std::unique_ptr<Element> product =
            std::make_unique<ElementLine>();

        return product;
    }
}
