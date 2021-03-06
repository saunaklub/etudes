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

#ifndef ETUDES_TRANSFORMS
#define ETUDES_TRANSFORMS

#include <glm/vec2.hpp>

#include <EtudesConfig.hpp>

#include <Graphics/Geometry/Rect.hpp>

namespace etudes {
    ETUDES_EXPORT glm::vec2 denormalize(const glm::vec2 &pos, const Rect &area);
}

#endif // ETUDES_TRANSFORMS
