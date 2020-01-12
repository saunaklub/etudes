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

#include <glm/glm.hpp>

#include <glow/common/str_utils.hh>

#include <glow/objects/Program.hh>
#include <glow/objects/Shader.hh>

#include <Utility/Utility.hpp>
#include <Graphics/Context.hpp>

#include "Shader.hpp"

namespace etudes {

    Shader::Shader(std::string filename,
                   Shader::MapType uniformMap) :
        filename(filename),
        uniformMap(uniformMap),
        quad(-1, -1, 1, 1)
    {}

    void Shader::init() {
        program = glow::Program::createFromFiles(
            {filename, glow::util::pathOf(__FILE__) + "/shader/shader.vsh"});
    }

    void Shader::registerInputs() {
        for(auto & entry : uniformMap) {
            registerInput(entry.first, vec_float_t{0});
        }
    }

    void Shader::draw() {
        Rect viewport = getContext().getViewport2D();

        auto shader = program->use();
        auto resolution = tg::vec2(viewport.getWidth(),
                                   viewport.getHeight());
        shader.setUniform("resolution", resolution);
        shader.setUniform("time", float(util::seconds()));

        for(auto & entry : uniformMap) {
            shader.setUniform(entry.second, getValue<float>(entry.first));
        }

        quad.draw();
    }
}
