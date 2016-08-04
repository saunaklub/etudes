/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <algorithm>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

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

    using logging::LogLevel;

    void Receiver::registerInput(string input,
                                 vec_int_t initialValue) {
        if(mapInputsInt.find(input) != mapInputsInt.end())
            log(LogLevel::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputsInt[input] = initialValue;
    }

    void Receiver::registerInput(string input,
                                 vec_float_t initialValue) {
        if(mapInputsFloat.find(input) != mapInputsFloat.end())
            log(LogLevel::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputsFloat[input] = initialValue;
    }

    void Receiver::registerInput(string input,
                                 vec_string_t initialValue) {
        if(mapInputsString.find(input) != mapInputsString.end())
            log(LogLevel::warning,
                "Receiver::registerInput: "s + input + " already registered");

        mapInputsString[input] = initialValue;
    }

    vector<string> Receiver::getInputs() const {
        vector<string> out;

        for(auto &pair : mapInputsInt)
            out.emplace_back(pair.first);
        for(auto &pair : mapInputsFloat)
            out.emplace_back(pair.first);
        for(auto &pair : mapInputsString)
            out.emplace_back(pair.first);

        return out;
    }

    template <> Receiver::vec_int_t
    Receiver::getInput<Receiver::vec_int_t>(std::string input) {
        std::lock_guard<std::mutex> guard(inputLock);

        const auto pair = mapInputsInt.find(input);
        if(pair == mapInputsInt.end()) {
            throw std::invalid_argument(
                "Receiver::getValue: input "s + input + " not registered");
        }
        return pair->second;
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
    void Receiver::setValue(string input, const vec_int_t &value) {
        std::lock_guard<std::mutex> guard(inputLock);

        if(mapInputsInt.find(input) == mapInputsInt.end())
            log(LogLevel::warning,
                "Receiver::setValue: input "s + input + " not registered");
        else
            mapInputsInt[input] = {value};
    }

    template <>
    void Receiver::setValue(string input, const vec_float_t &value) {
        std::lock_guard<std::mutex> guard(inputLock);

        if(mapInputsFloat.find(input) == mapInputsFloat.end())
            log(LogLevel::warning,
                "Receiver::setValue: input "s + input + " not registered");
        else
            mapInputsFloat[input] = {value};
    }

    template <>
    void Receiver::setValue(string input, const vec_string_t &value) {
        std::lock_guard<std::mutex> guard(inputLock);

        if(mapInputsString.find(input) == mapInputsString.end())
            log(LogLevel::warning,
                "Receiver::setValue: input "s + input + " not registered");
        else
            mapInputsString[input] = {value};
    }

    template <> int
    Receiver::getValue<int>(std::string input) {
        return getInput<vec_int_t>(input)[0];
    }

    template <> Receiver::vec_int_t
    Receiver::getValue<Receiver::vec_int_t>(std::string input) {
        return getInput<vec_int_t>(input);
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

    bool
    Receiver::dispatchValue(std::string path, const vec_int_t &value) {
        return dispatchValueT(path, value);
    }

    bool
    Receiver::dispatchValue(std::string path, const vec_float_t &value) {
        return dispatchValueT(path, value);
    }

    bool
    Receiver::dispatchValue(std::string path, const vec_string_t &value) {
        return dispatchValueT(path, value);
    }

    template <typename T> bool
    Receiver::dispatchValueT(std::string path, const T &value) {
        std::vector<std::string> inputs = getInputs();
        if(std::find(inputs.begin(), inputs.end(), path) != inputs.end()) {
            setValue(path, value);
            return true;
        }
        return false;
    }

}
