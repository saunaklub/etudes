#ifndef ETUDES_PARTICLES
#define ETUDES_PARTICLES

#include <vector>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <glm/glm.hpp>

#include <Utility/ShaderRegistry.hpp>
#include <Receivers/Element.hpp>

namespace etudes {
    class Particles : public Element {
    public:
        void registerInputs() override;
        void init() override;
        void draw() override;

    private:
        std::unique_ptr<ShaderRegistry> registry;

        gl::GLuint vao, vbo;
        std::vector<glm::vec2> particles;
    };
}

#endif // ETUDES_PARTICLES
