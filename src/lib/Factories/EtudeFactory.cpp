#include <string>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include <Factories/ElementFactory.hpp>

#include <Receivers/Etude.hpp>

#include "EtudeFactory.hpp"

namespace etudes {
    using logging::log;
    using logging::LogLevel;

    using YAML::Node;

    std::unique_ptr<Etude>
    EtudeFactory::makeEtude(const Node &node) {
        std::unique_ptr<Etude> product;

        if(node["type"]) {
            // special etudes
            std::string type = node["type"].as<std::string>();
        }
        else {
            // else
            product = makeEtudeDefault(node);
        }

        product->registerInputs();

        return product;
    }

    std::unique_ptr<Etude>
    EtudeFactory::makeEtudeDefault(const Node &node) {
        std::unique_ptr<Etude> product = std::make_unique<Etude>();

        log(LogLevel::debug, "Creating default etude");
        log(LogLevel::excessive, node["elements"]);

        std::map<std::string, Node> elements =
            node["elements"].as<std::map<std::string, Node>>();

        for(auto &element : elements)
            product->addElement(element.first,
                                ElementFactory::makeElement(element.second));

        return product;
    }

}
