#ifndef _ETUDES_ETUDESHOST
#define _ETUDES_ETUDESHOST

#include <vector>

class GLFWwindow;
class Render;

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
      bool initGLFW();
      bool initOSC();
      bool initRenderers();

      void processInput();
      void keyCallback(int, int, int, int);
      
      void nextRender();
      void prevRender();
      void printRender();

      void render();

      GLFWwindow *window;
      bool quitLoop;

      std::vector<Render*> renders;
      std::vector<Render*>::const_iterator curRender;
  };
}

#endif // _ETUDES_ETUDESHOST
