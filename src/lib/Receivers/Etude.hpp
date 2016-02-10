/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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
        void draw() override;

        void addElement(std::string name, std::unique_ptr<Element> element);
        void dispatchValue(std::string input, vec_t value);

    private:
        typedef std::map<std::string, std::unique_ptr<Element>> element_map_t;

        element_map_t elements;
    };
}

#endif // ETUDES_ETUDE
