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

#include <string>

#include <glbinding/gl/gl.h>
#include <glm/ext.hpp>

#include <Utility/Logging.hpp>

#include "Context.hpp"

namespace etudes {
    using namespace gl;

    using std::function;
    using std::vector;
    using std::pair;
    using std::make_pair;

    using glm::vec2;
    using glm::vec4;

    using std::to_string;
    using logging::to_string;

    using util::checkGLError;

    typedef std::vector<float> vec;

    Context::Context() :
        viewport2D(0, 0, 800, 600) {
    }

    void Context::init() {
        shaders.registerShader("mvp-uv", GL_VERTEX_SHADER,
                               {"resources/shaders/mvp-uv.vert"});
        shaders.registerShader("ident", GL_VERTEX_SHADER,
                               {"resources/shaders/ident.vert"});

        shaders.registerShader("white", GL_FRAGMENT_SHADER,
                               {"resources/shaders/white.frag"});
        shaders.registerShader("solid", GL_FRAGMENT_SHADER,
                                 {"resources/shaders/solid.frag"});
        shaders.registerShader("sinusoid", GL_FRAGMENT_SHADER,
                                 {"resources/shaders/sinusoid.frag"});
        shaders.registerShader("textured", GL_FRAGMENT_SHADER,
                               {"resources/shaders/textured-hueshift.frag"});
        shaders.registerShader("spiral", GL_FRAGMENT_SHADER,
                               {"resources/shaders/spiral.frag"});

        shaders.registerProgram("simple", {"ident", "white"});

        shaders.registerProgram("textured", {"mvp-uv", "textured"});
        shaders.registerUniform("textured", "mvp");
        shaders.registerUniform("textured", "hueShift");
        shaders.registerUniform("textured", "alpha");
        shaders.registerUniform("textured", "useAlpha");

        shaders.registerProgram("solid", {"mvp-uv", "solid"});
        shaders.registerUniform("solid", "mvp");
        shaders.registerUniform("solid", "color");

        shaders.registerProgram("sinusoid", {"mvp-uv", "sinusoid"});

        shaders.registerUniform("sinusoid", "mvp");
        shaders.registerUniform("sinusoid", "mode");

        shaders.registerUniform("sinusoid", "color");

        shaders.registerUniform("sinusoid", "circle_width");

        shaders.registerUniform("sinusoid", "stroke_width");
        shaders.registerUniform("sinusoid", "stroke_blur");

        shaders.registerUniform("sinusoid", "order");
        shaders.registerUniform("sinusoid", "time");
        shaders.registerUniform("sinusoid", "phase");
        shaders.registerUniform("sinusoid", "freq");
        shaders.registerUniform("sinusoid", "lambda");

        shaders.registerProgram("spiral", {"ident", "spiral"});
        shaders.registerUniform("spiral", "curl");
        shaders.registerUniform("spiral", "time");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);
        glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_ALWAYS);
//        glDepthFunc(GL_LESS);
//        glDepthFunc(GL_GREATER);
//        glDepthFunc(GL_EQUAL);
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

        checkGLError("context: init");
    }

    Rect Context::getViewport2D() const {
        return viewport2D;
    }

    void Context::setViewport2D(const Rect &viewport) {
        viewport2D = viewport;
    }

    glm::mat4 Context::getToViewportTransform() const {
        glm::mat4 toViewport(
            viewport2D.getWidth(),  0, 0, 0,
            0, viewport2D.getHeight(), 0, 0,
            0, 0, 1, 0,
            viewport2D.getPosX(), viewport2D.getPosY(), 0, 1);
        toViewport = glm::translate(toViewport, glm::vec3{0.5f, 0.5f, 0.f});

        return toViewport;
    }

    const glm::mat4 &Context::getProjection2D() const {
        return projOrtho;
    }

    void Context::setProjection2D(const Rect &viewport) {
        float tx = -(2*viewport.getPosX() / viewport.getWidth() + 1.f);
        float ty = -(2*viewport.getPosY() / viewport.getHeight() + 1.f);

        projOrtho = glm::mat4(
            2.f / viewport.getWidth(),  0, 0, 0,
            0, 2.f / viewport.getHeight(), 0, 0,
            0, 0, 1, 0,
            tx, ty, 0, 1);
    }

    const ShaderRegistry &Context::getShaderRegistry() const {
        return shaders;
    }

}
