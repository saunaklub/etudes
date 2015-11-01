#ifndef _ETUDES_ETUDETEMPLATE
#define _ETUDES_ETUDETEMPLATE

#include "Etude.hpp"

namespace etudes {
    class EtudeTemplate : public Etude {
    public:
        EtudeTemplate() {};
        virtual ~EtudeTemplate() {};
        
        std::string name() override;
        void draw() override;

    private:
    };
}

#endif // _ETUDES_ETUDETEMPLATE
