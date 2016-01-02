#ifndef ETUDES_ELEMENT
#define ETUDES_ELEMENT

#include <Receivers/Receiver.hpp>

namespace etudes {
    class Element : public Receiver {
    public:
        virtual void draw() = 0;

    private:
    };
}

#endif // ETUDES_ELEMENT
