#ifndef _ETUDES_SOURCE
#define _ETUDES_SOURCE

namespace etudes {

    /**
     * Source is the base class for all input data sources we want to
     * map to the inputs of the different Renderers. Examples could be
     * OSC, MIDI, Network, sensor, webfeed, random input, there shall
     * be no restrictions.
     *
     * @todo Think about a common representation which allows to treat
     * the value ranges of all inputs uniformly. For scalar values, we
     * settled on [0, 1]. Can we / do we need to think of other
     * representations for non-scalar, structured, vector
     * inputs?... Think...
     * claudio: Let's prepare a basic scalar OSC input, make a first 
     * working example and iterate. For the time being that will be enough...
     */
    class Source {
    public:
        

    private:
    };
}

#endif // _ETUDES_SOURCE
