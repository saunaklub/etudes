#ifndef ETUDES_ELEMENT
#define ETUDES_ELEMENT

#include <Graphics/Context.hpp>

#include <Receivers/Receiver.hpp>

namespace etudes {

    class Context;
    class Painter;

    class Element : public Receiver {
    public:
        virtual void init() {};
        virtual void update() {};
        virtual void draw(const Context &context,
                          const Painter &painter) = 0;

    private:
    };

}

#endif // ETUDES_ELEMENT
