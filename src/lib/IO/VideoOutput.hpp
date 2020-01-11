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

namespace etudes {

    class Scene;

    class VideoOutput {
    public:

        /**
         * Constructor.
         *
         * @param width Output width
         * @param height Output height
         */
        VideoOutput(std::string name, int width, int height);
        virtual ~VideoOutput();

        /**
         * Create the video API output.
         *
         * @param name Output name
         */
        virtual void create() = 0;

        /**
         * Render scene and output via video API.
         */
        virtual void render() = 0;

    protected:

        // /**
        //  * Create the specific video API output. Override this in
        //  * subclasses.
        //  *
        //  * @param name Output name
        //  */
        // virtual void doCreate(std::string name) = 0;

        /** Return the output name */
        std::string getName() const;

        /** Return output width */
        int getWidth() const;

        /** Return output height */
        int getHeight() const;

        /** Return currently active scene */
        Scene * getScene() const;

    private:
        std::string name;

        int width;
        int height;

        Scene *scene;
    };

}

#endif // ETUDES_VIDEOOUTPUT
