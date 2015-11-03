#ifndef _ETUDES_OSCSOURCE
#define _ETUDES_OSCSOURCE

#include "Input.hpp"
#include <lo/lo.h>

namespace etudes {
    class OSCInput : public Input {
    public:
        OSCInput(int iPort);
        virtual ~OSCInput();
        
        void update();
        
        bool doStart();
        void doStop();

    private:
        int m_iPort;
        
        lo_server_thread m_oscServer;
    };
}

#endif // _ETUDES_OSCSOURCE
