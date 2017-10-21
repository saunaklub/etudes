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

#ifndef ETUDES_VIDEOOUTPUT
#define ETUDES_VIDEOOUTPUT

#include <string>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

namespace etudes {

    class Scene;

    class VideoOutput {
    public:

        VideoOutput(Scene *scene, int width, int height);
        virtual ~VideoOutput();

        virtual void render() = 0;
        virtual void createOutput(std::string outputId) = 0;

    protected:

        void drawScene();

        int width;
        int height;

    private:

        Scene *scene;

    };

}

#endif // ETUDES_VIDEOOUTPUT
