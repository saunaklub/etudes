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

#ifndef ETUDES_ETUDESHOST
#define ETUDES_ETUDESHOST

#include <memory>
#include <vector>
#include <map>

#include <IO/OSCInput.hpp>

#include <Utility/Config.hpp>

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>

#include "Renderer.hpp"

struct GLFWwindow;

namespace etudes {
    class Scene;

    class EtudesHost {
    public:

        friend void key_callback(GLFWwindow* window,
                                 int key, int scancode, int action, int mods);
        friend void window_size_callback(GLFWwindow* window,
                                         int width, int height);

        EtudesHost();
        ~EtudesHost();

        void initialise();

        /**
         * @return Wether the application will continue to run, i.e. the
         *         user can do while(host.loopIteration()) {}.
         */
        bool loopIteration();

    private:

        void initGLFW();
        void initGL();
        void initOSC();
        void initScenes();
        void initInput();

        void printOpenGLInfo();
        void printFramerate();

        void registerMouseInput(Renderer::MouseInput mode, std::string path);
        void processInput();

        void keyCallback(int, int, int, int);
        void resizeCallback(int width, int height);

        void setCursorEnabled(bool enabled);

        void nextRenderer();
        void prevRenderer();
        void printCurrentRenderer();

        void render();
        void renderOutputs();
        void renderScreen();

        Config hostConfig;

        bool logFramerate;
        bool vsync;
        bool cursor;

        Rect::Scaling viewportScaling;
        GLFWwindow *window;

        bool paused;
        bool quitLoop;

        std::vector<std::unique_ptr<Renderer>> renderers;
        std::vector<std::unique_ptr<Renderer>>::const_iterator currentRenderer;

        OSCInput oscInput;

        std::unique_ptr<Context> context;
    };
}

#endif // ETUDES_ETUDESHOST
