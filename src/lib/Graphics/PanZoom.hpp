#ifndef ETUDES_PANZOOM
#define ETUDES_PANZOOM

#include <glm/vec2.hpp>

namespace etudes {

    class PanZoom {
    public:
        PanZoom();

        float getZoom();
        void setZoom(float zoom);

        float getAspectRatio();
        void setAspectRatio(float aspectRatio);

        float getSpeed();
        void setSpeed(float speed);

        glm::vec2 getCenter();
        void setCenter(glm::vec2 center);

        virtual glm::vec2 getXRange() = 0;
        virtual glm::vec2 getYRange() = 0;

    private:
        float zoom;
        float aspectRatio;
        float speed;

        glm::vec2 center;
    };

}

#endif // ETUDES_PANZOOM
