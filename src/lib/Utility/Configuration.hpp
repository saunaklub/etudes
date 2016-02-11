#ifndef ETUDES_CONFIGURATION
#define ETUDES_CONFIGURATION

#include <memory>

#include <yaml-cpp/yaml.h>

namespace etudes {

    class Configuration {
    public:
        void read(std::string file);
        void write(std::string file);

        template <typename T>
        T getValue(std::string path);
        bool hasValue(std::string path);

        YAML::Node getNode(std::string path);

        private:
        std::vector<std::string> parseFields(std::string path);

        std::unique_ptr<YAML::Node> config;
    };
}

#endif // ETUDES_CONFIGURATION
