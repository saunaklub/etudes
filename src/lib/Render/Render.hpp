#ifndef _ETUDES_RENDER
#define _ETUDES_RENDER

#include <string>

namespace etudes {
    class Render {
    public:
        virtual void render() = 0;
        virtual std::string name() = 0;

    private:
    };
}

#endif // _ETUDES_RENDER
