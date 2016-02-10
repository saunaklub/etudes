#include <functional>

#include <yaml-cpp/yaml.h>

#include <Utility/Logging.hpp>
#include <Utility/Utility.hpp>

#include <Elements/Lines.hpp>
#include <Elements/Particles.hpp>

#include "ElementFactory.hpp"

namespace etudes {

    using YAML::Node;
    using logging::LogLevel;

    std::map<std::string, ElementFactory::creation_t>
    ElementFactory::creationMap = {
        {"line", ElementFactory::createElement<Lines>},
        {"particles", ElementFactory::createElement<Particles>}
    };

    std::unique_ptr<Element>
    ElementFactory::makeElement(const Node &node) {
        std::unique_ptr<Element> product;

        std::string type = node["type"].as<std::string>();
        product = creationMap[type](node);

        product->registerInputs();

        if(node["defaults"]) {
            std::map<std::string, Node> defaults =
                node["defaults"].as<std::map<std::string, Node>>();
            for(auto &d : defaults) {
                product->setValue(
                    d.first,
                    d.second.as<std::vector<float>>());
            }
        }

        return product;
    }

}
