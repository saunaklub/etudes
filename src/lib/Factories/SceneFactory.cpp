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

#include <vector>
#include <string>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Utility/Config.hpp>

#include <Factories/ElementFactory.hpp>

#include <Receivers/Scene.hpp>

#include "SceneFactory.hpp"

namespace etudes {
    using logging::log;
    using logging::LogLevel;

    std::unique_ptr<Scene>
    SceneFactory::makeScene(std::string name,
                            const Config &configScene,
                            const Config &configGlobal) {

        log(LogLevel::excessive, configScene);
        std::unique_ptr<Scene> product = std::make_unique<Scene>();

        auto order = configScene.getValue<std::list<std::string>>("order");
        for(auto &element : order) {
            product->addElement(
                element, ElementFactory::makeElement(
                    configScene.getSubTree("elements:" + element),
                    configGlobal));
            log(LogLevel::excessive, "added element " + element);
        }

        product->registerInputs();

        if(configScene.hasValue("defaults")) {
            log(LogLevel::debug, configScene);
            for(auto &child : configScene.getChildren("defaults")) {
                auto path = "defaults:" + child;
                auto type = configScene.getType(path);

                switch(type) {
                case Config::Type::Scalar: {
                    auto value =
                        configScene.getValue<float>(path);
                    product->setValue(child, std::vector<float>{value});
                    break;
                }
                case Config::Type::Vector: {
                    auto values =
                        configScene.getValue<std::vector<float>>(path);
                    product->setValue(child, values);
                    break;
                }
                case Config::Type::Map:
                case Config::Type::Invalid: {
                    log(LogLevel::warning, "setting defaults for scene "
                        + name + ": default " + child +
                        " is not scalar or vector.");
                    break;
                }
                }
            }
        }

        return product;
    }

}
