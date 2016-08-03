#ifndef ETUDES_RENDERER
#define ETUDES_RENDERER

#include <memory>

#include <string>
#include <vector>

#include <Receivers/Scene.hpp>
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
                 std::unique_ptr<Scene> scene);

        std::string getName() const;

        void update();
        void render();

        void setOutput(std::string name, int width, int height);
        void renderOutput();

    private:

        std::string name;

        std::unique_ptr<Scene> scene;
        std::unique_ptr<VideoOutput> output;

        std::vector<std::pair<MouseInput, std::string>> inputsMouse;
    };

}

#endif // ETUDES_RENDERER
