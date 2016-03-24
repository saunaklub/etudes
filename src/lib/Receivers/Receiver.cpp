#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <Utility/Logging.hpp>

#include "Receiver.hpp"

using namespace std::literals::string_literals;

namespace etudes {
    using std::logic_error;
    using std::string;
    using std::vector;

    using glm::vec2;
    using glm::vec3;
    using glm::vec4;

    void Receiver::registerInput(string input,
                                 vec_t initialValue) {
        if(mapInputs.find(input) != mapInputs.end())
            log(logging::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputs[input] = initialValue;
    }

    vector<string> Receiver::getInputs() const {
        vector<string> out;

        for(auto &pair : mapInputs)
            out.emplace_back(pair.first);

        return out;
    }

    const Receiver::vec_t &Receiver::getInput(std::string input) const {
        const auto pair = mapInputs.find(input);
        if(pair == mapInputs.end()) {
            throw std::invalid_argument(
                "Receiver::getValue: input "s + input + " not registered");
        }
        return pair->second;
    }

    void Receiver::setValue(string input, vec_t value) {
        if(mapInputs.find(input) == mapInputs.end())
            throw std::invalid_argument(
                "Receiver::setValue: input "s + input + " not registered");
        else
            mapInputs[input] = {value};
    }

    template <> float
    Receiver::getValue<float>(std::string input) const {
        return getInput(input)[0];
    }

    template <> Receiver::vec_t
    Receiver::getValue<Receiver::vec_t>(std::string input) const {
        return getInput(input);
    }

    template <> vec2
    Receiver::getValue<vec2>(std::string input) const {
        const vec_t &vecInput = getInput(input);
        return vec2(vecInput[0], vecInput[1]);
    }

    template <> vec3
    Receiver::getValue<vec3>(std::string input) const {
        const vec_t &vecInput = getInput(input);
        return vec3(vecInput[0], vecInput[1], vecInput[2]);
    }

    template <> vec4
    Receiver::getValue<vec4>(std::string input) const {
        const vec_t &vecInput = getInput(input);
        return vec4(vecInput[0], vecInput[1], vecInput[2], vecInput[3]);
    }

}
