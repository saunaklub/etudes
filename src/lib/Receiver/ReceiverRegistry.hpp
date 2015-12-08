#ifndef ETUDES_RECEIVERREGISTRY
#define ETUDES_RECEIVERREGISTRY

#include <memory>
#include <map>
#include <string>
#include <iostream>

namespace etudes {
    class Receiver;

    class ReceiverRegistry {
    public:

        void registerReceiver(std::string name,
                              std::shared_ptr<Receiver> receiver);
        Receiver &getReceiver(std::string name);

    private:
        typedef std::map<std::string, std::shared_ptr<Receiver>> map_t;

        map_t registry;
    };
}

#endif // ETUDES_RECEIVERREGISTRY
