#ifndef ETUDES_CONFIGURATION
#define ETUDES_CONFIGURATION

#include <memory>

#include <yaml-cpp/yaml.h>

namespace etudes {

    class Configuration {
    public:
        friend std::ostream &operator<<(std::ostream &os,
                                        const Configuration &config);

        Configuration() {};

        void read(std::string file);
        void write(std::string file) const;

        bool hasValue(std::string path) const;
        template <typename T>
        T getValue(std::string path) const;

        std::vector<std::string> getChildren(std::string path) const;
        Configuration getSubTree(std::string path) const;

    private:
        Configuration(const YAML::Node &node);

        YAML::Node getNode(std::string path) const;
        std::unique_ptr<YAML::Node> config;
    };

    std::ostream &operator<<(std::ostream &os, const Configuration &config);
}

#endif // ETUDES_CONFIGURATION
