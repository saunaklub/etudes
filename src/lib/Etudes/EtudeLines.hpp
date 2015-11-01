#ifndef _ETUDES_ETUDELINES
#define _ETUDES_ETUDELINES

#include "Etude.hpp"

namespace etudes {
    class EtudeLines : public Etude {
    public:
        EtudeLines() {};
        virtual ~EtudeLines() {};
        
        std::string name() override;
        void draw() override;

    private:
    };
}

#endif // _ETUDES_ETUDELINES
