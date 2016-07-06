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

#ifndef ETUDES_ETUDE
#define ETUDES_ETUDE

#include <memory>
#include <string>

#include <Receivers/Element.hpp>

namespace etudes {

    class Etude : public Element {

    public:

        virtual ~Etude() {};

        void registerInputs() override;

        void init() override;
        void update() override;
        void draw(const Context &context,
                  const Painter &painter) override;

        void addElement(std::string name, std::unique_ptr<Element> element);

        template <typename T>
        void dispatchValue(std::string input, const T &value);

    protected:

        void clearBackground();

    private:

        typedef std::vector<std::pair<std::string, std::unique_ptr<Element>>>
                            element_vec_t;
        element_vec_t elements;
    };

}

#endif // ETUDES_ETUDE
