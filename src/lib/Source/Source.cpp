#include <exception>

#include "Source.hpp"

namespace etudes {
    
    Source::Source() :
        m_bStarted(false) {
    }

    Source::~Source() {
    }

    bool Source::start() {
        if(m_bStarted)
            throw std::logic_error("Source already started");

        bool success = doStart();

        m_bStarted = success;
	return success;
    }

    void Source::stop() {
        if(!m_bStarted)
            throw std::logic_error("Source not started");

        doStop();

        m_bStarted = true;
    }


    const Source::value_map & Source::getInputs() {
        return m_mapInputs;
    }

    float Source::getInput(string key) {
        return m_mapInputs[key];
    }

}
