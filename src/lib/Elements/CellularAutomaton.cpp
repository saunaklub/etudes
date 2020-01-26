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

#include <glm/ext.hpp>

#include <typed-geometry/tg.hh>

#include <glow/objects/Program.hh>
#include <glow/objects/Shader.hh>
#include <glow/objects/Texture2D.hh>

#include <Utility/Utility.hpp>
#include <Utility/Array2D.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>

#include "CellularAutomaton.hpp"

namespace etudes {

    using logging::LogLevel;

    CellularAutomaton::CellularAutomaton() :
        updateLast(0) {
        texData.resize(texWidth*texHeight);
    }

    void CellularAutomaton::registerInputs() {
        registerInput("rate", vec_float_t{1.f});
    }

    void CellularAutomaton::init() {
        program = glow::Program::createFromFiles(
            {"resources/shaders/ident-uv.vsh",
             "resources/shaders/textured.fsh"});

        texture = glow::Texture2D::create
            (texWidth, texHeight, GL_RGB);
        texture->setMipmapsGenerated(false);

        auto tex = texture->bind();
        tex.setFilter(GL_NEAREST, GL_NEAREST);
        tex.setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

        quad = std::make_unique<Quad>();
    }

    void CellularAutomaton::update() {
        float rate = getValue<float>("rate");
        // float delta_t = 1.f / rate;
        float delta_t = .1f;
        double time = util::seconds();

        if(time > updateLast + delta_t) {
            int updateCount = (time - updateLast) * rate;

            for(int step = 0 ; step < updateCount ; ++step) {
                advanceCA();
            }
            updateLast += updateCount * delta_t;
        }
    }

    void CellularAutomaton::advanceCA() {
        log(LogLevel::debug, "advancing...");
        randomizeTexture();
    }

    void CellularAutomaton::randomizeTexture() {
        for(int row = 0 ; row < texHeight ; ++row) {
            for(int col = 0 ; col < texWidth ; ++col) {
              auto value = tg::uniform(rng, tg::segment3({0,0,0}, {1,1,1}));
              texData[row*texWidth + col] = tg::vec3(value);
            }
        }

        auto tex = texture->bind();
        tex.setSubData(0, 0, texWidth, texHeight, texData);
    }

    void CellularAutomaton::draw() {
        auto shader = program->use();
        shader.setTexture("texSampler", texture);
        quad->draw();
    }
}
