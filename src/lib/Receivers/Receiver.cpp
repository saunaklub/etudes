#include <Utility/Logging.hpp>

#include "Receiver.hpp"

using namespace std::literals::string_literals;

namespace etudes {
    using std::logic_error;
    using std::string;
    using std::vector;

    vector<string> Receiver::getInputs() const {
        vector<string> out;

        for(auto &pair : mapInputs)
            out.emplace_back(pair.first);

        return out;
    }

    void Receiver::setValue(string input, vec_t value) {
        if(mapInputs.find(input) == mapInputs.end())
            log(logging::warning,
                "Receiver::setValue: input "s + input + " not registered");

        mapInputs[input] = {value};
    }

    void Receiver::registerInput(string input,
                                 vec_t initialValue) {
        if(mapInputs.find(input) != mapInputs.end())
            log(logging::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputs[input] = initialValue;
    }

    template <> float
    Receiver::getValue<float>(std::string input) const {
        using namespace std::literals::string_literals;

        const auto pair = mapInputs.find(input);
        if(pair == mapInputs.end())
            log(logging::warning,
                "Receiver::getValue: input "s + input + " not registered");

        return pair->second[0];
    }

}
