/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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

#ifndef ETUDES_ETUDESHOST
#define ETUDES_ETUDESHOST

#include <memory>
#include <vector>
#include <map>

#include <OSCInput.hpp>

#include <Utility/Configuration.hpp>

struct GLFWwindow;
class Etude;

namespace etudes {
    class EtudesHost {
    public:
        friend void key_callback(GLFWwindow* window,
                                 int key, int scancode, int action, int mods);

        EtudesHost();
        ~EtudesHost();

        bool initialise();

        /**
         * @return Wether the application will continue to run, i.e. the
         *         user can do while(host.loopIteration()) {}.
         */
        bool loopIteration();

    private:
        typedef std::map<std::string, std::unique_ptr<Etude>> etude_map_t;

        // @todo: use exceptions for error handling!
        bool initGLFW();
        void initOSC();
        bool initEtudes();

        void processInput();
        void keyCallback(int, int, int, int);

        void nextEtude();
        void prevEtude();

        void render();

        GLFWwindow *window;
        bool quitLoop;

        etude_map_t etudes;
        etude_map_t::const_iterator currentEtude;

        OSCInput oscInput;

        Configuration hostConfig;
        Configuration etudesConfig;
    };
}

#endif // ETUDES_ETUDESHOST
