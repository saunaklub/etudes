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

    using namespace logging;

    Shader::Shader(std::string shaderFragment,
                   std::string shaderVertex,
                   Shader::MapType uniformMap) :
        shaderFragment(shaderFragment),
        shaderVertex(shaderVertex),
        uniformMap(uniformMap),
        quad(-1, -1, 1, 1)
    {}

    void Shader::init() {
        program = glow::Program::createFromFiles({shaderFragment,
                                                  shaderVertex});
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
            auto values = getValue<std::vector<float>>(entry.first);

            switch(values.size()) {
            case 1:
                shader.setUniform(entry.second, values[0]);
                break;
            case 2:
                shader.setUniform
                    (entry.second,
                     tg::vec2(values[0], values[1]));
                break;
            case 3:
                shader.setUniform
                    (entry.second,
                     tg::vec3(values[0], values[1], values[2]));
                break;
            case 4:
                shader.setUniform
                    (entry.second,
                     tg::vec4(values[0], values[1], values[2], values[3]));
                break;
            default:
                log(LogLevel::error,
                    "generic uniform values need length 1, 2, 3 or 4");
                break;
            }
        }

        quad.draw();
    }
}
