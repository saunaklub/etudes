#ifndef _ETUDES_ETUDE
#define _ETUDES_ETUDE

#include <string>

namespace etudes {
    class Etude {
    public:
        virtual void draw() = 0;
        virtual std::string name() = 0;
      virtual ~Etude() {};
    private:
    };
}

#endif // _ETUDES_ETUDE
