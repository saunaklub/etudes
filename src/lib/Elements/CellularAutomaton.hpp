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

#ifndef ETUDES_CELLULAR_AUTOMATON
#define ETUDES_CELLULAR_AUTOMATON

#include <memory>

#include <typed-geometry/tg-lean.hh>

#include <glow/fwd.hh>

#include <Graphics/Texture.hpp>
#include <Graphics/Drawable/Quad.hpp>

#include <Receivers/Element.hpp>

namespace etudes {
    class CellularAutomaton : public Element {
    public:
        CellularAutomaton();

        void registerInputs() override;
        void init() override;
        void update() override;
        void draw() override;

        void randomizeTexture();
        void advanceCA();

    private:
        const int texWidth = 100;
        const int texHeight = 100;
        std::vector<tg::vec3> texData;

        double updateLast;
        tg::rng rng;

        glow::SharedProgram program;
        glow::SharedTexture2D texture;
        std::unique_ptr<Quad> quad;
    };
}

#endif // ETUDES_CELLULAR_AUTOMATON
