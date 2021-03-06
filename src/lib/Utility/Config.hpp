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

#ifndef ETUDES_CONFIGURATION
#define ETUDES_CONFIGURATION

#include <memory>

#include <yaml-cpp/yaml.h>

#include <EtudesConfig.hpp>

namespace etudes {

    class ETUDES_EXPORT Config {
    public:

    enum class Type {
        Scalar,
        Vector,
        Map,
        Invalid
    };

    friend std::ostream &operator<<(std::ostream &os,
                                    const Config &config);

    Config() {};

    void read(std::string file);
    void write(std::string file) const;

    bool hasValue(std::string path) const;
    template <typename T>
    T getValue(std::string path) const;

    std::vector<std::string> getChildren(std::string path) const;
    Config getSubTree(std::string path) const;

    Type getType(std::string path) const;

    private:
    Config(const YAML::Node &node);

    YAML::Node getNode(std::string path) const;
    std::unique_ptr<YAML::Node> config;
    };

    std::ostream &operator<<(std::ostream &os, const Config &config);
}

#endif // ETUDES_CONFIGURATION
