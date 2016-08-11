/*

  Études Audiovisuels - Graphical elements for audiovisual composition.
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

#ifndef ETUDES_RECEIVER
#define ETUDES_RECEIVER

#include <string>
#include <vector>
#include <map>
#include <mutex>

#include <Utility/Logging.hpp>

namespace etudes {

    class Receiver {
    public:

        typedef std::vector<int> vec_int_t;
        typedef std::vector<float> vec_float_t;
        typedef std::vector<std::string> vec_string_t;

        virtual void
        registerInputs() = 0;

        std::vector<std::string>
        getInputs() const;

        template <typename T> void
        setValue(std::string input, const T &value);

        template <typename T> T
        getValue(std::string input);

        virtual bool
        dispatchValue(std::string input, const vec_int_t &value);

        virtual bool
        dispatchValue(std::string input, const vec_float_t &value);

        virtual bool
        dispatchValue(std::string input, const vec_string_t &value);

    protected:

        Receiver() = default;

        void
        registerInput(std::string input,
                      vec_int_t initialValue = {0});

        void
        registerInput(std::string input,
                      vec_float_t initialValue = {0});

        void
        registerInput(std::string input,
                      vec_string_t initialValue = {""});

    private:

        typedef std::map<std::string, vec_int_t> input_map_int_t;
        typedef std::map<std::string, vec_float_t> input_map_float_t;
        typedef std::map<std::string, vec_string_t> input_map_string_t;

        template <typename T> bool
        dispatchValueT(std::string input, const T &value);

        template <class T> T
        getInput(std::string input);

        input_map_int_t mapInputsInt;
        input_map_float_t mapInputsFloat;
        input_map_string_t mapInputsString;

        std::mutex inputLock;
    };

}

#endif // ETUDES_RECEIVER
