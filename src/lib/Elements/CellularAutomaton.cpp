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

#include <glbinding/gl/gl.h>

#include <glm/ext.hpp>

#include <Utility/Utility.hpp>
#include <Utility/Array2D.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>

#include "CellularAutomaton.hpp"

namespace etudes {

    using namespace gl;
    using logging::LogLevel;

    CellularAutomaton::CellularAutomaton() :
        updateLast(0) {
    }
    
    void CellularAutomaton::registerInputs() {
        registerInput("/rate", vec_float_t{1.f});
    }

    void CellularAutomaton::init() {
        int texWidth = 100;
        int texHeight = 100;

        quad = std::make_unique<Quad>();
        texture = std::make_unique<Texture>(texWidth, texHeight,
                                            Texture::NEAREST, false);
    }

    void CellularAutomaton::update() {
        float rate = getValue<float>("/rate");

        double time = seconds();
        if(time > updateLast + 1.f / rate) {
            int updateCount = (time - updateLast) * rate;
            updateLast += updateCount * 1.f / rate;

            for(int step = 0 ; step < updateCount ; ++step)
                advanceCA();
        }
    }

    void CellularAutomaton::advanceCA() {
        log(LogLevel::debug, "advancing...");
        randomizeTexture();
    }

    void CellularAutomaton::randomizeTexture() {
        Array2D<unsigned char> texData(texture->mapData(),
                                       texture->getWidth());

        for(int row = 0 ; row < texture->getHeight() ; ++row) {
            for(int col = 0 ; col < texture->getWidth() ; ++col) {
                texData[row][col] = rand() % (255) + rand() / (row+1);
            }
        }

        texture->unmapData();
    }

    void CellularAutomaton::draw(const Context &context,
                                 const Painter &painter) {

        const ShaderRegistry &registry = context.getShaderRegistry();

        glUseProgram(registry.getProgram("textured"));

        Rect area = context.getViewport2D();
        
        glm::mat4 model(
            area.getWidth(),  0, 0, 0,
            0, area.getHeight(), 0, 0,
            0, 0, 1, 0,
            area.getPosX(), area.getPosY(), 0, 1);
        model = glm::translate(model, glm::vec3{0.5f, 0.5f, 0.f});
        glm::mat4 mvp = context.getProjection2D() * model;

        GLint locMVP = registry.getUniform("textured", "mvp");
        glUniformMatrix4fv(locMVP, 1, GLboolean(false),
                           glm::value_ptr(mvp));

        texture->draw();
    }
}
