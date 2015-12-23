#include <string>

#include <Util/Logging.hpp>
#include <Etudes/Etude.hpp>

#include "EtudeFactory.hpp"

namespace etudes {
    using logging::log;
    using logging::LogLevel;

    using YAML::Node;

    std::unique_ptr<Etude>
    EtudeFactory::makeEtude(const Node &node) {
        std::unique_ptr<Etude> product;

        std::string type = node["type"].as<std::string>();
        // special etudes

        // else
        product = makeEtudeDefault(node);

        return product;
    }

    std::unique_ptr<Etude>
    EtudeFactory::makeEtudeDefault(const Node &node) {
        std::unique_ptr<Etude> product = std::make_unique<Etude>();

        log(LogLevel::debug, "Creating default Etude");

        log(LogLevel::excessive, node["elements"]);

        std::list<Node> elements =
            node["elements"].as<std::list<Node>>();

        return product;
    }

}
