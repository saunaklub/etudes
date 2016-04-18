#ifndef ETUDES_PANZOOMPARALLEL
#define ETUDES_PANZOOMPARALLEL

#include <Graphics/PanZoom.hpp>

namespace etudes {

    class PanZoomParallel :
        public PanZoom {
    public:
        glm::vec2 getXRange() override;
        glm::vec2 getYRange() override;

    private:
    };

}

#endif // ETUDES_PANZOOMPARALLEL
