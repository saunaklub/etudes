#ifndef _ETUDES_OSCSOURCE
#define _ETUDES_OSCSOURCE

#include "Source.hpp"
#include <lo/lo.h>

namespace etudes {
    class OSCSource : public Source {
    public:
        OSCSource(int iPort);
        virtual ~OSCSource();
        
        void update();
        
        bool doStart();
        void doStop();

    private:
        int m_iPort;
        
        lo_server_thread m_oscServer;
    };
}

#endif // _ETUDES_OSCSOURCE
