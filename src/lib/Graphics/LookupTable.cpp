#include <string_view>

#include <glow/objects/Texture1D.hh>

#include <Utility/Utility.hpp>

#include "LookupTable.hpp"

namespace etudes
{
    LookupTable::LookupTable() {
        lookupTable = glow::Texture1D::create(256, GL_RGBA32F);
    }

    void
    LookupTable::addControlPoint
    (glm::vec4 color, float t)
    {
        nodes.insert({color, t});
    }

    void
    LookupTable::generate()
    {
        // for(float t = 0.0f ; t <= 1.0f ; t += 0.05) {
        //     auto c = closest(nodes, t);
        //     EDB(c.second);
        // }
    }

    // LookupTable::Node
    // LookupTable::closest
    // (const Cont & container, float value)
    // {
    //     typename Cont::const_reverse_iterator cri =
    //         std::lower_bound(container.rbegin(),
    //                          container.rend(),
    //                          value, Cont::key_compare());
    //     if (cri != container.rend()) {
    //         return *cri;
    //     }
    //     return *container.rend();
    // }

}
