/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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

#include <string>
#include <iostream>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Receivers/Etude.hpp>

#include "OSCInput.hpp"

using namespace std::literals::string_literals;

namespace {
    void error(int num, const char *msg, const char *path) {
        log(etudes::logging::error,
            "liblo error "s + std::to_string(num) +
            "at "s + path + ": "s + msg);
    }

    int float_handler(const char *path, const char *types, lo_arg ** argv,
                      int argc, void *data, void *user_data) {

        etudes::OSCInput* router =
            static_cast<etudes::OSCInput*>(user_data);

        std::vector<float> values;
        for(int arg = 0 ; arg < argc ; ++arg) {
            if(types[arg] != 'f') {
                log(etudes::logging::warning,
                    "OSC handler: unexpected argument type: "s + types[arg]);
                continue;
            }

            values.emplace_back(argv[arg]->f);
        }

        router->update(path, std::move(values));

        return 0;
    }

}

namespace etudes {

    using std::string;
    using logging::LogLevel;

    OSCInput::OSCInput(const etude_map_t &etudes, int port) :
        etudes(etudes),
        port(port),
        started(false) {
    }

    OSCInput::~OSCInput() {
        if(lo_server_thread_stop(oscServer) == 0)
            lo_server_thread_free(oscServer);
    }

    void OSCInput::start() {
        if(started)
            throw std::logic_error("OSCInput::start: already started");

        oscServer = lo_server_thread_new(
            std::to_string(port).c_str(), error);

        lo_server_thread_add_method(
            oscServer, NULL, "f",
            float_handler, this);

        if(lo_server_thread_start(oscServer) != 0)
            throw(std::runtime_error(
                      "OSCInput::start: "
                      "failed to start osc server thread"));

        started = true;
    }

    void OSCInput::stop() {
        if(!started)
            throw std::logic_error(
                "OSCInput::stop: osc server thread not running");

        // @todo: tear down osc server thread!
        //started = false;
    }

    void OSCInput::update(std::string path,
                          std::vector<float> values) {
        string etude = splitStringFirst(path);
        string input = splitStringRest(path);

        logging::log(LogLevel::excessive, etude + ": " + input);
        logging::log(LogLevel::excessive, values);

        auto iter = etudes.find(etude);
        if(iter != etudes.end())
            iter->second->dispatchValue(input, std::move(values));
    }

}
