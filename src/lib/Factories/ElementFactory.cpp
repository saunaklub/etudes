#include <functional>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Utility/Configuration.hpp>

#include <Elements/Lines.hpp>
#include <Elements/Particles.hpp>
#include <Elements/ImageView.hpp>

#include <Graphics/PanZoomParallel.hpp>

#include "ElementFactory.hpp"

namespace etudes {

    using logging::LogLevel;

    std::map<std::string, ElementFactory::creation_t>
    ElementFactory::creationMap = {
        {"line", ElementFactory::createElement<Lines>},
        {"particles", ElementFactory::createElement<Particles>},
        {"imageview", ElementFactory::createElementImageView},
    };

    std::unique_ptr<Element>
    ElementFactory::makeElement(const Configuration &config) {
        std::unique_ptr<Element> product;

        std::string type = config.getValue<std::string>("type");
        try {
            product = creationMap[type](config);
        } catch(std::bad_function_call) {
            log(LogLevel::error,
                "no factory method defined for element type: " + type);
        }

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

    std::unique_ptr<Element>
    ElementFactory::createElementImageView(const Configuration & config) {
        std::string image = config.getValue<std::string>("image");
        std::unique_ptr<PanZoom> panZoom;

        if(config.hasValue("panZoom")) {
            std::string panZoomName = config.getValue<std::string>("panZoom");
            if(panZoomName == "parallel") {
                panZoom = std::make_unique<PanZoomParallel>();
            }
            else
                log(LogLevel::warning, "unknown pan/zoom strategy: " +
                    panZoomName);
        }

        return std::make_unique<ImageView>(image, std::move(panZoom));
    }
}
