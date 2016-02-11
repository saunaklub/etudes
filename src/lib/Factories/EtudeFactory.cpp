#include <vector>
#include <string>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Utility/Configuration.hpp>

#include <Factories/ElementFactory.hpp>

#include <Receivers/Etude.hpp>

#include "EtudeFactory.hpp"

namespace etudes {
    using logging::log;
    using logging::LogLevel;

    std::unique_ptr<Etude>
    EtudeFactory::makeEtude(std::string name, const Configuration &config) {
        std::unique_ptr<Etude> product;

        if(config.hasValue("type")) {
            std::string type = config.getValue<std::string>("type");
        }
        else {
            log(LogLevel::debug, "Creating default etude '" + name + "'");
            product = makeEtudeDefault(config);
        }

        product->registerInputs();

        return product;
    }

    std::unique_ptr<Etude>
    EtudeFactory::makeEtudeDefault(const Configuration &config) {
        std::unique_ptr<Etude> product = std::make_unique<Etude>();

        log(LogLevel::excessive, config);

        for(auto &child : config.getChildren("elements")) {
            log(LogLevel::debug, child);
            product->addElement(
                child, ElementFactory::makeElement(
                    config.getSubTree("elements:" + child)));
        }

        return product;
    }

}
