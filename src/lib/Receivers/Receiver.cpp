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
                                 vec_float_t initialValue) {
        if(mapInputsFloat.find(input) != mapInputsFloat.end())
            log(logging::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputsFloat[input] = initialValue;
    }

    void Receiver::registerInput(string input,
                                 vec_string_t initialValue) {
        if(mapInputsString.find(input) != mapInputsString.end())
            log(logging::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputsString[input] = initialValue;
    }

    vector<string> Receiver::getInputs() const {
        vector<string> out;

        for(auto &pair : mapInputsFloat)
            out.emplace_back(pair.first);
        for(auto &pair : mapInputsString)
            out.emplace_back(pair.first);

        return out;
    }

    template <> Receiver::vec_float_t
    Receiver::getInput<Receiver::vec_float_t>(std::string input) {
        std::lock_guard<std::mutex> guard(inputLock);

        const auto pair = mapInputsFloat.find(input);
        if(pair == mapInputsFloat.end()) {
            throw std::invalid_argument(
                "Receiver::getValue: input "s + input + " not registered");
        }
        return pair->second;
    }

    template <> Receiver::vec_string_t
    Receiver::getInput<Receiver::vec_string_t>(std::string input) {
        std::lock_guard<std::mutex> guard(inputLock);

        const auto pair = mapInputsString.find(input);
        if(pair == mapInputsString.end()) {
            throw std::invalid_argument(
                "Receiver::getValue: input "s + input + " not registered");
        }
        return pair->second;
    }

    template <>
    void Receiver::setValue(string input, const vec_float_t &value) {
        std::lock_guard<std::mutex> guard(inputLock);

        if(mapInputsFloat.find(input) == mapInputsFloat.end())
            throw std::invalid_argument(
                "Receiver::setValue: input "s + input + " not registered");
        else
            mapInputsFloat[input] = {value};
    }

    template <>
    void Receiver::setValue(string input, const vec_string_t &value) {
        std::lock_guard<std::mutex> guard(inputLock);

        if(mapInputsString.find(input) == mapInputsString.end())
            throw std::invalid_argument(
                "Receiver::setValue: input "s + input + " not registered");
        else
            mapInputsString[input] = {value};
    }

    template <> float
    Receiver::getValue<float>(std::string input) {
        return getInput<vec_float_t>(input)[0];
    }

    template <> Receiver::vec_float_t
    Receiver::getValue<Receiver::vec_float_t>(std::string input) {
        return getInput<vec_float_t>(input);
    }

    template <> vec2
    Receiver::getValue<vec2>(std::string input) {
        vec_float_t vecInput = getInput<vec_float_t>(input);
        return vec2(vecInput[0], vecInput[1]);
    }

    template <> vec3
    Receiver::getValue<vec3>(std::string input) {
        vec_float_t vecInput = getInput<vec_float_t>(input);
        return vec3(vecInput[0], vecInput[1], vecInput[2]);
    }

    template <> vec4
    Receiver::getValue<vec4>(std::string input) {
        vec_float_t vecInput = getInput<vec_float_t>(input);
        return vec4(vecInput[0], vecInput[1], vecInput[2], vecInput[3]);
    }

    template <> std::string
    Receiver::getValue<std::string>(std::string input) {
        vec_string_t vecInput = getInput<vec_string_t>(input);
        return vecInput[0];
    }

    template <> Receiver::vec_string_t
    Receiver::getValue<Receiver::vec_string_t>(std::string input) {
        vec_string_t vecInput = getInput<vec_string_t>(input);
        return vecInput;
    }
}
