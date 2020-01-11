/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <yaml-cpp/yaml.h>

#include <EtudesConfig.hpp>

#include <Utility/Utility.hpp>
#include <Utility/Logging.hpp>

#include "Config.hpp"

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

    using YAML::Node;
    using YAML::LoadFile;
    using YAML::BadFile;
    using YAML::Clone;

    using logging::LogLevel;

    Config::Config(const Node &node) :
        config(std::make_unique<Node>(node)) {
    }


    void Config::read(std::string file) {
        try {
            config = std::make_unique<Node>();
            *config = LoadFile(file);
        } catch (BadFile &e) {
            std::string message = "Unable to load config: "s + file;
            logging::log(LogLevel::error, message);
            throw std::runtime_error(message);
        }
    }

    void Config::write(std::string file) const {
    }

    bool Config::hasValue(std::string path) const {
        if(getNode(path).IsNull()) {
            return false;
        }
        return true;
    }

    template <typename T>
    T Config::getValue(std::string path) const {
        return getNode(path).as<T>();
    }

    std::vector<std::string>
    Config::getChildren(std::string path) const {
        std::vector<std::string> children;
        Node node = getNode(path);

        for(auto &child : node.as<std::map<std::string, Node>>()) {
            children.push_back(child.first);
        }

        return children;
    }

    Config Config::getSubTree(std::string path) const {
        // log(LogLevel::debug, "path: " + path);
        // log(LogLevel::debug, "config:");
        // log(LogLevel::debug, *config.get());
        // log(LogLevel::debug, getNode(path));
        return Config(getNode(path));
    }

    Config::Type Config::getType(std::string path) const {
        Node node = getNode(path);

        if(node.IsScalar())
            return Type::Scalar;
        else if(node.IsSequence())
            return Type::Vector;
        else if(node.IsMap())
            return Type::Map;
        else
            return Type::Invalid;
    }

    Node Config::getNode(std::string path) const {
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

    std::ostream &operator<<(std::ostream &os, const Config &config) {
        os << config.getNode("");
        return os;
    }

    template ETUDES_EXPORT bool
    Config::getValue<bool>(std::string path) const;

    template ETUDES_EXPORT int
    Config::getValue<int>(std::string path) const;

    template ETUDES_EXPORT std::string
    Config::getValue<std::string>(std::string path) const;
    template ETUDES_EXPORT std::list<std::string>
    Config::getValue<std::list<std::string>>(std::string path) const;

    template ETUDES_EXPORT float
    Config::getValue<float>(std::string path) const;
    template ETUDES_EXPORT std::vector<float>
    Config::getValue<std::vector<float>>(std::string path) const;

}
