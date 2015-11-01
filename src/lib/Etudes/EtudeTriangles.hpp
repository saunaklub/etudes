#ifndef _ETUDES_ETUDETRIANGLES
#define _ETUDES_ETUDETRIANGLES

#include "Etude.hpp"

namespace etudes {
    class EtudeTriangles : public Etude {
    public:
        EtudeTriangles() {};
        virtual ~EtudeTriangles() {};
        
        std::string name() override;
        void draw() override;

    private:
    };
}

#endif // _ETUDES_ETUDETRIANGLES
