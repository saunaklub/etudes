#ifndef _ETUDES_RENDERER
#define _ETUDES_RENDERER

namespace etudes {
    class Renderer {
    public:
        Renderer() {};
        virtual ~Renderer() {};
        
        virtual void render() = 0;

    private:
    };
}

#endif // _ETUDES_RENDERER
