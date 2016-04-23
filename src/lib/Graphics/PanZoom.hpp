#ifndef ETUDES_PANZOOM
#define ETUDES_PANZOOM

#include <Graphics/Geometry/Rect.hpp>

namespace etudes {

    class PanZoom {
    public:
        PanZoom();
        virtual ~PanZoom();

        float getSpeed();
        void setSpeed(float speed);

        virtual Rect getSourceArea();
        void setSourceArea(const Rect &area);

    private:
        float speed;
        Rect sourceArea;
    };

}

#endif // ETUDES_PANZOOM
