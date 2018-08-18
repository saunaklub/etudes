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

#include <Utility/Utility.hpp>

#include <glow/objects/TextureRectangle.hh>
#include <glow/objects/Texture3D.hh>
#include <glow/objects/Framebuffer.hh>
#include <glow/objects/Program.hh>

#include <glow/common/scoped_gl.hh>
#include <glow/common/str_utils.hh>

#include <Graphics/Geometry/Transforms.hpp>

#include "FlowTrace.hpp"

namespace
{
    typedef struct
    {
        uint64_t state;
        uint64_t inc;
    } pcg32_random_t;

    uint32_t pcg32_random_r(pcg32_random_t* rng)
    {
        uint64_t oldstate = rng->state;
        // Advance internal state
        rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
        // Calculate output function (XSH RR), uses old state for max ILP
        uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
        uint32_t rot = oldstate >> 59u;
        return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
    }
}

namespace etudes {

    using namespace glow;

    void FlowTrace::registerInputs()
    {
    }

    void FlowTrace::init()
    {
        mShader = Program::createFromFiles(
            {glow::util::pathOf(__FILE__) + "/flowtrace/identity.vsh",
             glow::util::pathOf(__FILE__) + "/flowtrace/flowtrace.fsh"});
        mShaderOutput = Program::createFromFiles(
            {glow::util::pathOf(__FILE__) + "/flowtrace/identity.vsh",
             glow::util::pathOf(__FILE__) + "/flowtrace/output.fsh"});

        Rect viewport = getContext().getViewport2D();

        mResultA = TextureRectangle::create(viewport.getWidth(),
                                            viewport.getHeight(), GL_RGBA32F);
        mResultB = TextureRectangle::create(viewport.getWidth(),
                                            viewport.getHeight(), GL_RGBA32F);
        mFBOA = Framebuffer::create({{"outColor", mResultA}});
        mFBOB = Framebuffer::create({{"outColor", mResultB}});

        mNoise = Texture3D::create(128, 128, 128, GL_RGBA32F);
        pcg32_random_t s = {17, 17};
        std::vector<glm::vec4> data;
        while (data.size() < 128 * 128 * 128) {
            // float val = pcg32_random_r(&s) / (float)std::numeric_limits<uint32_t>::max();
            // data.push_back({val, val, val, 1});
            data.push_back({pcg32_random_r(&s) / (float)std::numeric_limits<uint32_t>::max(),
                            pcg32_random_r(&s) / (float)std::numeric_limits<uint32_t>::max(),
                            pcg32_random_r(&s) / (float)std::numeric_limits<uint32_t>::max(),
                            pcg32_random_r(&s) / (float)std::numeric_limits<uint32_t>::max()});
        }
        mNoise->bind().setData(GL_RGBA32F, 128, 128, 128, data);
        mNoise->bind().generateMipmaps();
    }

    void FlowTrace::update()
    {
    }

    void FlowTrace::draw()
    {
        GLOW_SCOPED(disable, GL_CULL_FACE);
        GLOW_SCOPED(disable, GL_DEPTH_TEST);
        // GLOW_SCOPED(enable, GL_BLEND);
        // GLOW_SCOPED(blendFunc, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Rect viewport = getContext().getViewport2D();

        {
            auto shader = mShader->use();
            shader.setUniform("uWidth", int(viewport.getWidth()));
            shader.setUniform("uHeight", int(viewport.getHeight()));
            shader.setUniform("uTime", float(util::seconds()));
            shader.setUniform("uSteps", 5);
            shader.setTexture("uNoise", mNoise);

            {
                auto fb = mFBOA->bind();

                static bool first = true;
                if (first)
                {
                    glClearColor(0, 0, 0, 1);
                    glClear(GL_COLOR_BUFFER_BIT);
                    first = false;
                }

                shader.setTexture("uTexture", mResultB);
                quad.draw();
            }
            {
                auto fb = mFBOB->bind();
                shader.setTexture("uTexture", mResultA);
                quad.draw();
            }
        }

        auto shader = mShaderOutput->use();
        shader.setTexture("uTexture", mResultB);

        quad.draw();
    }

}
