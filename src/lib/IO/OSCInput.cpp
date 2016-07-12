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
#include <string>
#include <iostream>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>
#include <Receivers/Etude.hpp>

#include "OSCInput.hpp"

using namespace std::literals::string_literals;

namespace {
    using etudes::logging::log;
    using etudes::logging::LogLevel;

    void error(int num, const char *msg, const char *path) {
        log(etudes::logging::error,
            "liblo error "s + std::to_string(num) +
            "at "s + path + ": "s + msg);
    }

    int handler(const char *path, const char *types, lo_arg ** argv,
                      int argc, void *data, void *user_data) {

        etudes::OSCInput* oscInput =
            static_cast<etudes::OSCInput*>(user_data);

        if(types[0] == 'i') {
            std::vector<int> values;
            for(int arg = 0 ; arg < argc ; ++arg) {
                if(types[arg] != 'i') {
                    log(etudes::logging::warning,
                        "OSC handler: unexpected argument type: "s + types[arg]);
                    continue;
                }

                values.emplace_back(argv[arg]->i);
            }
            oscInput->update(path, std::move(values));
        }

        else if(types[0] == 'f') {
            std::vector<float> values;
            for(int arg = 0 ; arg < argc ; ++arg) {
                if(types[arg] != 'f') {
                    log(etudes::logging::warning,
                        "OSC handler: unexpected argument type: "s + types[arg]);
                    continue;
                }

                values.emplace_back(argv[arg]->f);
            }
            oscInput->update(path, std::move(values));
        }
        else if(types[0] == 's') {
            std::vector<std::string> values;
            for(int arg = 0 ; arg < argc ; ++arg) {
                if(types[arg] != 's') {
                    log(etudes::logging::warning,
                        "OSC handler: unexpected argument type: "s + types[arg]);
                    continue;
                }

                values.emplace_back(&argv[arg]->s);
            }
            oscInput->update(path, std::move(values));
        }

        return 0;
    }

}

namespace etudes {

    using std::string;
    using logging::LogLevel;

    OSCInput::OSCInput(int port) :
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
            oscServer, nullptr, nullptr,
            handler, this);

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

    template <typename T>
    void OSCInput::update(std::string path,
                          const T &values) {
        string receiver = splitStringFirst(path);
        string input = splitStringRest(path);

        logging::log(LogLevel::excessive, receiver + ": " + input);
        logging::log(LogLevel::excessive, values);

        auto iter = std::find_if(receivers.begin(), receivers.end(),
                                 [&](const auto &e)  {
                                     return(e.first == receiver);
                                 });
        if(iter != receivers.end())
            iter->second->dispatchValue(input, std::move(values));
    }

    template
    void OSCInput::update(std::string path,
                          const std::vector<float> &values);

    bool OSCInput::addReceiver(std::string name, 
                                std::shared_ptr<Receiver> receiver) {
        auto iter = std::find_if(receivers.begin(), receivers.end(),
                                 [&](const auto &e)  {
                                     return(e.first == name);
                                 });
        if(iter != receivers.end()) {
            log(LogLevel::warning, "OSCInput::addReceiver "s + name +
                                        " already added!"s);
            return false;
        }

        else {
            receivers[name] = receiver;
            return true;
        }
    }
}
