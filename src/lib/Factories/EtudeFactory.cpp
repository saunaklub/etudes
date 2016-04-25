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
            log(LogLevel::info, "Creating default etude '" + name + "'");
            product = makeEtudeDefault(config);
        }

        product->registerInputs();

        return product;
    }

    std::unique_ptr<Etude>
    EtudeFactory::makeEtudeDefault(const Configuration &config) {
        std::unique_ptr<Etude> product = std::make_unique<Etude>();

        log(LogLevel::excessive, config);

        auto order = config.getValue<std::list<std::string>>("order");
        for(auto &element : order) {
            product->addElement(
                element, ElementFactory::makeElement(
                    config.getSubTree("elements:" + element)));
            log(LogLevel::excessive, "added element " + element);
        }

        return product;
    }

}
