#pragma once

#include <set>

#include <glm/glm.hpp>

#include <glow/fwd.hh>

namespace etudes
{
    /* parametric LUT from Catmull-Rom interpolated nodes */
    class LookupTable {
    public:
        using Node = std::pair<glm::vec4, float>;
        struct Compare {
            bool operator()(const Node& lhs, const Node& rhs) const {
                return lhs.second < rhs.second;
            }
        };

        using Cont = std::set<Node, Compare>;

        LookupTable();

        void addControlPoint(glm::vec4 color, float t);
        void generate();

    private:
        Node closest(const Cont & container, float value);

        Cont nodes;
        glow::SharedTexture1D lookupTable;
    };
}
