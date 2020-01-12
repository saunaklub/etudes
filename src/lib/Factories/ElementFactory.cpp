/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <functional>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Utility/Config.hpp>

#include <Elements/Lines.hpp>
#include <Elements/Particles.hpp>
#include <Elements/ImageView.hpp>
#include <Elements/Sinusoids.hpp>
#include <Elements/CellularAutomaton.hpp>
#include <Elements/AlgoSynth.hpp>
#include <Elements/BlobTraces.hpp>
#include <Elements/Spiral.hpp>
#include <Elements/DomainWarp.hpp>
#include <Elements/MultiFractal.hpp>
#include <Elements/SimplexField.hpp>
#include <Elements/Clouds.hpp>
#include <Elements/Shader.hpp>
#include <Elements/FlowTrace.hpp>
#include <Elements/Testbed.hpp>

#include <Graphics/PanZoomParallel.hpp>

#include "ElementFactory.hpp"

namespace etudes {

    using logging::LogLevel;

    std::map<std::string, ElementFactory::creation_t>
    ElementFactory::creationMap = {
        {"Line", ElementFactory::createElement<Lines>},
        {"Particles", ElementFactory::createElement<Particles>},
        {"ImageView", ElementFactory::createElementImageView},
        {"Sinusoids", ElementFactory::createElement<Sinusoids>},
        {"CellularAutomaton", ElementFactory::createElement<CellularAutomaton>},
        {"AlgoSynth", ElementFactory::createElement<AlgoSynth>},
        {"BlobTraces", ElementFactory::createElement<BlobTraces>},
        {"Spiral", ElementFactory::createElement<Spiral>},
        {"DomainWarp", ElementFactory::createElement<DomainWarp>},
        {"MultiFractal", ElementFactory::createElement<MultiFractal>},
        {"SimplexField", ElementFactory::createElement<SimplexField>},
        {"Clouds", ElementFactory::createElement<Clouds>},
        {"Shader", ElementFactory::createElement<Shader>},
        {"FlowTrace", ElementFactory::createElement<FlowTrace>},
        {"Testbed", ElementFactory::createElement<Testbed>},
    };

    std::unique_ptr<Element>
    ElementFactory::makeElement(const Config & configElement,
                                const Config & configGlobal) {

        std::unique_ptr<Element> product;

        std::string typeElement = configElement.getValue<std::string>("type");
        try {
            product = creationMap[typeElement](configElement, configGlobal);
        } catch(std::bad_function_call&) {
            log(LogLevel::error,
                "no factory method defined for element type: " + typeElement);
        }

        product->registerInputs();

        if(configElement.hasValue("defaults")) {
            log(LogLevel::debug, configElement);
            for(auto &child : configElement.getChildren("defaults")) {
                auto path = "defaults:" + child;
                auto type = configElement.getType(path);

                switch(type) {
                case Config::Type::Scalar: {
                    auto value =
                        configElement.getValue<float>(path);
                    product->setValue(child, std::vector<float>{value});
                    break;
                }
                case Config::Type::Vector: {
                    auto values =
                        configElement.getValue<std::vector<float>>(path);
                    product->setValue(child, values);
                    break;
                }
                case Config::Type::Map:
                case Config::Type::Invalid: {
                    log(LogLevel::warning, "setting defaults for element type "
                        + typeElement + ": default " + child +
                        " is not scalar or vector.");
                    break;
                }
                }
            }
        }

        return product;
    }

    std::unique_ptr<Element>
    ElementFactory::createElementImageView(const Config &configElement,
                                           const Config &configGlobal) {
        std::string image = configElement.getValue<std::string>("image");
        std::unique_ptr<PanZoom> panZoom;

        if(configElement.hasValue("panZoom")) {
            std::string panZoomName =
                configElement.getValue<std::string>("panZoom");
            if(panZoomName == "parallel") {
                panZoom = std::make_unique<PanZoomParallel>();
            }
            else
                log(LogLevel::warning, "unknown pan/zoom strategy: " +
                    panZoomName);
        }

        std::unique_ptr<Element> product =
            std::make_unique<ImageView>(image, std::move(panZoom));;

        return product;
    }

    template <>
    std::unique_ptr<Element>
    ElementFactory::createElement<Shader>(const Config &configElement,
                                          const Config &configGlobal) {
        auto shaderPath = configGlobal.getValue<std::string>("paths:shaders");
        auto shaderFragment = shaderPath + "/" +
            configElement.getValue<std::string>("fragment");
        auto shaderVertex = shaderPath + "/shader.vsh";

        if(configElement.hasValue("vertex")) {
            shaderVertex = shaderPath + "/" +
                configElement.getValue<std::string>("vertex");
        }

        auto uniformMappings = Shader::MapType{};
        if(configElement.hasValue("uniforms")) {
            log(LogLevel::debug, configElement);
            for(auto &child : configElement.getChildren("uniforms")) {
                auto path = "uniforms:" + child;

                auto inputName = child;
                auto uniformName = configElement.getValue<std::string>(path);

                std::cout << "adding {" << child << ", " << uniformName << "}"
                          << std::endl;

                uniformMappings.push_back({inputName, uniformName});
            }
        }

        std::unique_ptr<Element> product =
            std::make_unique<Shader>(shaderFragment, shaderVertex,
                                     uniformMappings);

        return product;
    }

}
