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

#include <glm/glm.hpp>

#include <EtudesConfig.hpp>

#include <Graphics/Geometry/Rect.hpp>

#ifndef ETUDES_CONTEXT
#define ETUDES_CONTEXT

namespace etudes {

    class ETUDES_EXPORT Context {
    public:
        Context();

        void init();

        Rect getViewport2D() const;
        void setViewport2D(const Rect &viewport);
        glm::mat4 getToViewportTransform() const;

        const glm::mat4 &getProjection2D() const;
        void setProjection2D(const Rect &projection);

    private:
        Rect viewport2D;
        glm::mat4 projOrtho;
    };

}

#endif // ETUDES_CONTEXT
