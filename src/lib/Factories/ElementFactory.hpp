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

#ifndef ETUDES_ELEMENTFACTORY
#define ETUDES_ELEMENTFACTORY

#include <memory>
#include <map>
#include <string>

#include <Receivers/Element.hpp>

namespace etudes {
    class Configuration;
    class Context;
    class Painter;

    class ElementFactory {
    public:
        static std::unique_ptr<Element>
        makeElement(const Configuration &config,
                    const Context &context,
                    const Painter &painter);

    private:
        typedef std::function<
        std::unique_ptr<Element>(const Configuration &,
                                 const Context & context,
                                 const Painter & painter)> creation_t;

        static std::map<std::string, creation_t> creationMap;

        template <typename T> static
        std::unique_ptr<Element>
        createElement(const Configuration &config,
                      const Context &context,
                      const Painter &painter) {

            std::unique_ptr<Element> product =
                std::make_unique<T>();

            product->context = &context;
            product->painter = &painter;

            return product;
        }

        static std::unique_ptr<Element>
        createElementImageView(const Configuration &,
                               const Context & context,
                               const Painter & painter);
    };
}

#endif // ETUDES_ELEMENTFACTORY
