#ifndef _ETUDES_ETUDESHOST
#define _ETUDES_ETUDESHOST

#include <vector>

class GLFWwindow;
class Render;

namespace etudes {
  class EtudesHost {
    public:
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
      void render();

      GLFWwindow *window;
      bool quitLoop;

      std::vector<Render*> renders;
      std::vector<Render*>::const_iterator curRender;
  };
}

#endif // _ETUDES_ETUDESHOST
