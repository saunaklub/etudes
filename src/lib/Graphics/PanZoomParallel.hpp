#ifndef ETUDES_PANZOOMPARALLEL
#define ETUDES_PANZOOMPARALLEL

#include <Graphics/PanZoom.hpp>

namespace etudes {

    class PanZoomParallel :
        public PanZoom {
    public:
        Rect getSourceArea() override;

    private:
    };

}

#endif // ETUDES_PANZOOMPARALLEL
