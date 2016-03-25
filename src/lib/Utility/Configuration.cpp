#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <yaml-cpp/yaml.h>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include "Configuration.hpp"

using namespace std::string_literals;

namespace {
    std::vector<std::string> parseFields(std::string path) {
        std::istringstream ssPath(path);
        std::string field;
        std::vector<std::string> fields;

        while(std::getline(ssPath, field, ':')) {
            fields.push_back(field);
        }

        return fields;
    }
}

namespace etudes {

    using std::cerr;
    using std::endl;

    using YAML::Node;
    using YAML::LoadFile;
    using YAML::BadFile;
    using YAML::Clone;

    using logging::LogLevel;

    Configuration::Configuration(const Node &node) :
        config(std::make_unique<Node>(node)) {
    }


    void Configuration::read(std::string file) {
        try {
            config = std::make_unique<Node>();
            *config = LoadFile(file);
        } catch (BadFile &e) {
            cerr <<
                "Unable to load file at relative path " <<
                file << endl;
        }
    }

    void Configuration::write(std::string file) const {
    }

    bool Configuration::hasValue(std::string path) const {
        if(getNode(path).IsNull()) {
            return false;
        }
        return true;
    }

    template <typename T>
    T Configuration::getValue(std::string path) const {
        return getNode(path).as<T>();
    }

    std::vector<std::string>
    Configuration::getChildren(std::string path) const {
        std::vector<std::string> children;
        Node node = getNode(path);

        for(auto &child : node.as<std::map<std::string, Node>>()) {
            children.push_back(child.first);
        }

        return children;
    }

    Configuration Configuration::getSubTree(std::string path) const {
        // log(LogLevel::debug, "path: " + path);
        // log(LogLevel::debug, "config:");
        // log(LogLevel::debug, *config.get());
        // log(LogLevel::debug, getNode(path));
        return Configuration(getNode(path));
    }

    Node Configuration::getNode(std::string path) const {
        std::vector<std::string> fields = parseFields(path);

        Node node = Clone(*config);
        auto field = fields.begin();
        for(; field < fields.end() ; ++field) {
            if(node[*field])
                node = node[*field];
            else
                return Node();
        }
        return node;
    }

    std::ostream &operator<<(std::ostream &os, const Configuration &config) {
        os << config.getNode("");
        return os;
    }

    template bool
    Configuration::getValue<bool>(std::string path) const;

    template int
    Configuration::getValue<int>(std::string path) const;

    template std::string
    Configuration::getValue<std::string>(std::string path) const;

    template std::list<std::string>
    Configuration::getValue<std::list<std::string>>(std::string path) const;

    template std::vector<float>
    Configuration::getValue<std::vector<float>>(std::string path) const;

}
