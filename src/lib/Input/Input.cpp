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
