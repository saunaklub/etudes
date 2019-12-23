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

#include <glbinding/gl/gl.h>

#include <glow/common/str_utils.hh>

#include <glow/objects/Program.hh>
#include <glow/objects/Shader.hh>

#include <Utility/Utility.hpp>
#include <Graphics/Context.hpp>

#include "Shader.hpp"

namespace etudes {

    using namespace gl;

    Shader::Shader(std::string filename) :
        filename(filename),
        quad(-1, -1, 1, 1)
    {}

    void Shader::init() {
        program = glow::Program::createFromFile
            (glow::util::pathOf(__FILE__) + "/shader/" + filename);

        lut.addControlPoint({1, 0, 0, 1}, 0.0);
        lut.addControlPoint({0, 1, 0, 1}, 0.5);
        lut.addControlPoint({1, 0, 1, 1}, 1.0);

        lut.generate();
    }

    void Shader::registerInputs() {
        registerInput("in1", vec_float_t{0});
        registerInput("in2", vec_float_t{0});
        registerInput("in3", vec_float_t{0});
        registerInput("in4", vec_float_t{0});
        registerInput("in5", vec_float_t{0});
        registerInput("in6", vec_float_t{0});
        registerInput("in7", vec_float_t{0});
        registerInput("in8", vec_float_t{0});
        registerInput("env", vec_float_t{0});
        registerInput("brightness", vec_float_t{0});
        registerInput("invert", vec_float_t{0});
    }

    void Shader::draw() {
        Rect viewport = getContext().getViewport2D();

        auto shader = program->use();
        auto resolution = glm::vec2(viewport.getWidth(),
                                    viewport.getHeight());
        shader.setUniform("resolution", resolution);
        shader.setUniform("time", float(util::seconds()));

        shader.setUniform("in1", getValue<float>("in1"));
        shader.setUniform("in2", getValue<float>("in2"));
        shader.setUniform("in3", getValue<float>("in3"));
        shader.setUniform("in4", getValue<float>("in4"));
        shader.setUniform("in5", getValue<float>("in5"));
        shader.setUniform("in6", getValue<float>("in6"));
        shader.setUniform("in7", getValue<float>("in7"));
        shader.setUniform("in8", getValue<float>("in8"));
        shader.setUniform("env", getValue<float>("env"));
        shader.setUniform("brightness", getValue<float>("brightness"));
        shader.setUniform("invert", getValue<float>("invert"));

        quad.draw();
    }
}
