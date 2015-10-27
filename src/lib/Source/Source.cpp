#include <exception>

#include "Source.hpp"

namespace etudes {
    
    Source::Source() :
        m_bStarted(false) {
    }

    Source::~Source() {
    }

    void Source::start() {
        if(m_bStarted)
            throw std::logic_error("Source already started");

        doStart();

        m_bStarted = true;
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
