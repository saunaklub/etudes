#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <Util/Utilities.hpp>

#include "Configuration.hpp"

using namespace std::string_literals;

namespace etudes {
    using YAML::Node;
    using YAML::LoadFile;
    using YAML::Clone;

    void Configuration::read(std::string file) {
        config = std::make_unique<Node>();
        *config = LoadFile(file);
    }

    void Configuration::write(std::string file) {
    }

    Node Configuration::getNode(std::string path) {
        std::vector<std::string> fields = parseFields(path);

        Node node = Clone(*config);
        auto field = fields.begin();
        for(; field < fields.end() ; ++field) {
            if(node[*field])
                node = node[*field];
            else
                throw std::invalid_argument(
                    "Configuration: field "s + *field +
                    " not found in configuration path " + path);
        }
        return node;
    }

    template <typename T>
    T Configuration::getValue(std::string path) {
        return getNode(path).as<T>();
    }

    std::vector<std::string> Configuration::parseFields(std::string path) {
        std::istringstream ssPath(path);
        std::string field;
        std::vector<std::string> fields;

        while(std::getline(ssPath, field, '/')) {
            fields.push_back(field);
        }

        return fields;
    }

    template std::string Configuration::getValue<std::string>(std::string path);
    template std::list<std::string>
    Configuration::getValue<std::list<std::string>>(std::string path);
    template int Configuration::getValue<int>(std::string path);
}
