#include <glm/gtc/constants.hpp>

#include "Render/ModulationFuncs.hpp"

#include "EtudeLines.hpp"


namespace etudes {
    using glm::pi;
    using glm::vec2;
    using glm::vec3;
    
    void EtudeLines::draw() {

        render.drawParallels(
            vec2(-0.5, -0.5),
            vec2( 0.5,  0.5),
            50, 50,
            funcConst(2),          // width
            funcSin(0.01f, 0.005f, pi<float>()/20.0f), // distance
            funcConst(vec3(1,1,1)) // color
            );
    }

    std::string EtudeLines::name() {
        return "Lines";
    }
}
