#ifndef _ETUDES_ETUDESHOST
#define _ETUDES_ETUDESHOST

#include <vector>

class GLFWwindow;
class Renderer;

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

      std::vector<Renderer*> renderers;
  };
}

#endif // _ETUDES_ETUDESHOST
