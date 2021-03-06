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

#ifndef ETUDES_PAINTER
#define ETUDES_PAINTER

#include <functional>

#include <glm/glm.hpp>

#include <glow/fwd.hh>

#include <EtudesConfig.hpp>

#include <Graphics/ShaderRegistry.hpp>
#include <Graphics/Geometry/Rect.hpp>
#include <Graphics/Drawable/Quad.hpp>

namespace etudes {

    class Context;

    class ETUDES_EXPORT Painter {
    public:

    Painter();

    void reset();

    void setContext(const Context & context);

    void setColor(glm::vec4 color);
    void setInputNormalized(bool normalized);

    void drawLine(glm::vec2 p0, glm::vec2 p1, float width);

    void drawRect(Rect rect);
    void drawRect(glm::vec2 topLeft, glm::vec2 bottomRight);
    void drawRect(glm::vec2 center, float size);

    void drawSinusoidStraight(
        glm::vec2 p0, glm::vec2 p1, int order, float width,
        float lambda, float phase,
        float strokeWidth, float strokeBlur) const;

    void drawSinusoidCircular(
        glm::vec2 center, int order, float width, float height,
        float lambda, float phase, float phaseCircular,
        float circleWidth, float strokeWidth, float strokeBlur) const;

    void drawParallels(
        glm::vec2 centerp0, glm::vec2 centerp1,
        int leftRepeat, int rightRepeat,
        std::function<float(int)> funcWidth,
        std::function<float(int)> funcDistance,
        std::function<glm::vec4(int)> funcColor);

    private:

    void drawLineGeometry(glm::vec2 p0, glm::vec2 p1, float width,
                          glow::UsedProgram &shader) const;
    void drawCircleGeometry(glm::vec2 center, float width, float height,
                            glow::UsedProgram &shader) const;

    const Context * context;
    Quad quad;

    glm::vec4 color;
    bool normalizedInput;

    ShaderRegistry shaders;

    glow::SharedProgram programSolid;
    glow::SharedProgram programSinusoid;
    };
}

#endif // ETUDES_PAINTER
