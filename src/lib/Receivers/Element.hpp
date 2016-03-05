#ifndef ETUDES_ELEMENT
#define ETUDES_ELEMENT

#include <Receivers/Receiver.hpp>

namespace etudes {

    class ShaderRegistry;
    class Painter;

    class Element : public Receiver {
    public:
        virtual void init(ShaderRegistry &registry) {};
        virtual void update() {};
        virtual void draw(const ShaderRegistry &registry,
                          const Painter &painter) = 0;

    private:
    };

}

#endif // ETUDES_ELEMENT
