#ifndef ETUDES_RENDERER
#define ETUDES_RENDERER

#include <memory>

#include <string>
#include <vector>

#include <Receivers/Etude.hpp>
#include <IO/VideoOutput.hpp>

namespace etudes {

    class Renderer {
    public:

        enum class MouseInput {
            MOUSE_X,
            MOUSE_Y,
            MOUSE_XY
        };

        Renderer(std::string name,
                 std::shared_ptr<Etude> etude);

        std::string getName() const;

        void update();
        void render(Context &context, Painter &painter);

        void addOutput(std::string name, int width, int height);
        void renderOutput(Context &context, Painter &painter);

    private:

        std::string name;

        std::shared_ptr<Etude> etude;
        std::unique_ptr<VideoOutput> output;

        std::vector<std::pair<MouseInput, std::string>> inputsMouse;
    };

}

#endif // ETUDES_RENDERER
