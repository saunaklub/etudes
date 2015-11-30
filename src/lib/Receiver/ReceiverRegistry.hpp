#ifndef _ETUDES_RECEIVERREGISTRY
#define _ETUDES_RECEIVERREGISTRY

#include <memory>
#include <string>

#include "Receiver.hpp"

namespace etudes {
    class ReceiverRegistry {
    public:

        void registerReceiver(std::string name,
                              std::shared_ptr<Receiver> receiver);

        std::shared_ptr<Receiver>
        getReceiver(std::string name);

    private:
        typedef std::map<std::string, std::shared_ptr<Receiver>> map_t;

        map_t registry;              
    };
}

#endif // _ETUDES_RECEIVERREGISTRY
