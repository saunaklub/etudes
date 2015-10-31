#ifndef _ETUDES_RENDER
#define _ETUDES_RENDER

namespace etudes {
    class Render {
    public:
        Render() {};
        virtual ~Render() {};
        
        virtual void render() = 0;

    private:
    };
}

#endif // _ETUDES_RENDER
