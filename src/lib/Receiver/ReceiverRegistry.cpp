#include "ReceiverRegistry.hpp"

namespace etudes {

    void ReceiverRegistry::registerReceiver(
        std::string name,
        std::shared_ptr<Receiver> receiver) {

        if(registry.find("name") != registry.end())
            throw std::logic_error(
                std::string("ReceiverRegistry::registerReceiver: ") +
                name + " already registered");

        registry[name] = receiver;            
    }

    Receiver &ReceiverRegistry::getReceiver(std::string name) {
        auto pair = registry.find(name);
        if(pair == registry.end())
            throw std::logic_error(
                std::string("ReceiverRegistry::registerReceiver: ") +
                name + " not registered");
        return *(pair->second);
    }

}
