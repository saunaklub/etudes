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
#include <Utility/Configuration.hpp>

#include <Elements/Lines.hpp>
#include <Elements/Particles.hpp>
#include <Elements/ImageView.hpp>
#include <Elements/Sinusoids.hpp>
#include <Elements/CellularAutomaton.hpp>
#include <Elements/AlgoSynth.hpp>
#include <Elements/BlobTraces.hpp>
#include <Elements/Spiral.hpp>
#include <Elements/DomainWarp.hpp>
#include <Elements/Truchet.hpp>
#include <Elements/MultiFractal.hpp>
#include <Elements/SimplexField.hpp>
#include <Elements/Clouds.hpp>
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
        {"Truchet", ElementFactory::createElement<Truchet>},
        {"DomainWarp", ElementFactory::createElement<DomainWarp>},
        {"MultiFractal", ElementFactory::createElement<MultiFractal>},
        {"SimplexField", ElementFactory::createElement<SimplexField>},
        {"Clouds", ElementFactory::createElement<Clouds>},
        {"Testbed", ElementFactory::createElement<Testbed>},
    };

    std::unique_ptr<Element>
    ElementFactory::makeElement(const Configuration & config) {
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

        std::unique_ptr<Element> product =
            std::make_unique<ImageView>(image, std::move(panZoom));;

        return product;
    }
}
