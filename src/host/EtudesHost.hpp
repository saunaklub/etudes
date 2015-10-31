#ifndef _ETUDES_ETUDESHOST
#define _ETUDES_ETUDESHOST

class GLFWwindow;

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

      GLFWwindow *window;
  };
}

#endif // _ETUDES_ETUDESHOST
