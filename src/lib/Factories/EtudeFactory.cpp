/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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
#include <Utility/Configuration.hpp>

#include <Factories/ElementFactory.hpp>

#include <Receivers/Etude.hpp>

#include "EtudeFactory.hpp"

namespace etudes {
    using logging::log;
    using logging::LogLevel;

    std::shared_ptr<Etude>
    EtudeFactory::makeEtude(std::string name,
                            const Configuration &config,
                            const Context & context,
                            Painter & painter) {
        std::shared_ptr<Etude> product;

        if(config.hasValue("type")) {
            std::string type = config.getValue<std::string>("type");
        }
        else {
            log(LogLevel::info, "Creating default etude '" + name + "'");
            product = makeEtudeDefault(config, context, painter);
        }

        product->context = &context;
        product->painter = &painter;

        auto order = config.getValue<std::list<std::string>>("order");
        for(auto &element : order) {
            product->addElement(
                element, ElementFactory::makeElement(
                    config.getSubTree("elements:" + element),
                    context, painter));
            log(LogLevel::excessive, "added element " + element);
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

    std::shared_ptr<Etude>
    EtudeFactory::makeEtudeDefault(const Configuration & config,
                                   const Context & context,
                                   Painter & painter) {
        log(LogLevel::excessive, config);
        std::shared_ptr<Etude> product = std::make_shared<Etude>();
        return product;
    }

}
