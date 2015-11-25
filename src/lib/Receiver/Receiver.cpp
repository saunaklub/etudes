#include <exception>

#include "Receiver.hpp"

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
            throw logic_error(
                string("Receiver::setValue: input ") + input +
                " not registered");

        mapInputs[input] = value;
    }

    void Receiver::registerInput(string input,
                                 float initialValue) {
        if(mapInputs.find(input) != mapInputs.end())
            throw logic_error(
                string("Receiver::registerInput: ") + input +
                " already registered");
                
        mapInputs[input] = initialValue;
    }
}
