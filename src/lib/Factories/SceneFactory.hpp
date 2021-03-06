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

#ifndef ETUDES_SCENEFACTORY
#define ETUDES_SCENEFACTORY

#include <memory>

#include <EtudesConfig.hpp>

namespace etudes {

    class Scene;
    class Config;

    class ETUDES_EXPORT SceneFactory {
    public:
        static std::unique_ptr<Scene>
        makeScene(std::string name,
                  const Config &configScene,
                  const Config &configGlobal);

    private:
    };

}

#endif // ETUDES_SCENEFACTORY
