#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <Utility/Utility.hpp>

#include "Configuration.hpp"

using namespace std::string_literals;

namespace etudes {
    using std::cerr;
    using std::endl;
    using YAML::Node;
    using YAML::LoadFile;
    using YAML::BadFile;
    using YAML::Clone;

    void Configuration::read(std::string file) {
        try {
            config = std::make_unique<Node>();
            *config = LoadFile(file);
        } catch (BadFile e) {
            cerr <<
                "Unable to load file at relative path " <<
                file << endl;
        }
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
                return Node();
        }
        return node;
    }

    bool Configuration::hasValue(std::string path) {
        if(getNode(path).IsNull()) {
            return false;
        }
        return true;
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
    template bool Configuration::getValue<bool>(std::string path);
}
