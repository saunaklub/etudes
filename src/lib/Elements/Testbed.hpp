#ifndef ETUDES_TESTBED
#define ETUDES_TESTBED

#include <Receivers/Element.hpp>

namespace etudes {
    class Testbed : public Element {
    public:
        void registerInputs() override;
        void draw(const Context &context,
                  const Painter &painter) override;

    private:
    };
}

#endif // ETUDES_TESTBED
