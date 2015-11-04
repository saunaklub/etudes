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

#include <exception>

#include "Input.hpp"

namespace etudes {
    
    Input::Input() :
        m_bStarted(false) {
    }

    Input::~Input() {
    }

    bool Input::start() {
        if(m_bStarted)
            throw std::logic_error("Input already started");

        bool success = doStart();

        m_bStarted = success;
	return success;
    }

    void Input::stop() {
        if(!m_bStarted)
            throw std::logic_error("Input not started");

        doStop();

        m_bStarted = true;
    }


    const Input::value_map & Input::getInputs() {
        return m_mapInputs;
    }

    float Input::getInput(string key) {
        return m_mapInputs[key];
    }

}
