#ifndef ETUDES_ELEMENT
#define ETUDES_ELEMENT

#include <Receivers/Receiver.hpp>

namespace etudes {

    class Painter;

    class Element : public Receiver {
    public:
        virtual void init() {};
        virtual void update() {};
        virtual void draw(const Painter &painter) = 0;

    private:
    };

}

#endif // ETUDES_ELEMENT
