#include <Utility/Logging.hpp>

#include "PartialAura.hpp"

namespace etudes {

    using logging::LogLevel;

    void PartialAura::registerInputs() {
        registerInput("/partials", {});
    }

    void PartialAura::draw(const Context &context,
                           const Painter &painter) {
        auto partials = getValue<vec_t>("/partials");
        log(LogLevel::excessive, partials);
    }
}
