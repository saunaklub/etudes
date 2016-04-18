#ifndef ETUDES_LINES
#define ETUDES_LINES

#include <Receivers/Element.hpp>

namespace etudes {
    class Lines : public Element {
    public:
        void registerInputs() override;
        void draw(const Context &context) override;

    private:
    };
}

#endif // ETUDES_LINES
