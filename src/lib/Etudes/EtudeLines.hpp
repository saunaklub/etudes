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

#ifndef ETUDES_ETUDELINES
#define ETUDES_ETUDELINES

#include <Render/RenderPrimitives.hpp>

#include "Etude.hpp"

namespace etudes {
    class EtudeLines : public Etude {
    public:
        EtudeLines();
        virtual ~EtudeLines();

        std::string whoami() override;
        void draw() override;

    private:
        RenderPrimitives render;
    };
}

#endif // ETUDES_ETUDELINES
