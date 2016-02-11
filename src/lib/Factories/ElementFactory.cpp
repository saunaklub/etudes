#include <functional>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Utility/Configuration.hpp>

#include <Elements/Lines.hpp>
#include <Elements/Particles.hpp>

#include "ElementFactory.hpp"

namespace etudes {

    using logging::LogLevel;

    std::map<std::string, ElementFactory::creation_t>
    ElementFactory::creationMap = {
        {"line", ElementFactory::createElement<Lines>},
        {"particles", ElementFactory::createElement<Particles>}
    };

    std::unique_ptr<Element>
    ElementFactory::makeElement(const Configuration &config) {
        std::unique_ptr<Element> product;

        std::string type = config.getValue<std::string>("type");
        product = creationMap[type](config);

        product->registerInputs();

        if(config.hasValue("defaults")) {
            log(LogLevel::debug, config);
            for(auto &child : config.getChildren("defaults")) {
                product->setValue(
                    child, config.getValue<std::vector<float>>(
                        "defaults:" + child));
            }
        }

        return product;
    }

}
