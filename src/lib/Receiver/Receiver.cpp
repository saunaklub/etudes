#include <iostream>

#include <Util/Logging.hpp>

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

    void Receiver::setValue(string input, float value) {
        if(mapInputs.find(input) == mapInputs.end())
            log(warning,
                "Receiver::setValue: input "s + input + " not registered");

        mapInputs[input] = value;
    }

    float Receiver::getValue(string input) const {
        const auto pair = mapInputs.find(input);
        if(pair == mapInputs.end())
            log(warning,
                "Receiver::getValue: input "s + input + " not registered");

        return pair->second;
    }

    void Receiver::registerInput(string input,
                                 float initialValue) {
        if(mapInputs.find(input) != mapInputs.end())
            log(warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputs[input] = initialValue;
    }
}
