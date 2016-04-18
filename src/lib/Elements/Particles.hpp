#ifndef ETUDES_PARTICLES
#define ETUDES_PARTICLES

#include <vector>
#include <random>

#include <glbinding/gl/gl.h>

#include <glm/glm.hpp>

#include <Utility/ShaderRegistry.hpp>
#include <Receivers/Element.hpp>

namespace etudes {
    class Particles : public Element {
    public:
        Particles();

        void registerInputs() override;

        void init() override;
        void update() override;
        void draw(const Context &context) override;

    private:
        void initGL();

        void updateBest();

        gl::GLuint vao, vbo;

        int count;
        glm::vec2 center;

        std::vector<glm::vec2> positions;
        std::vector<glm::vec2> positionsIBest;
        glm::vec2 positionGBest;

        std::vector<glm::vec2> velocities;

        std::random_device randDev;
        std::mt19937 randGen;

        ShaderRegistry shaders;
    };
}

#endif // ETUDES_PARTICLES
