#ifndef ETUDES_IMAGEVIEW
#define ETUDES_IMAGEVIEW

#include <memory>

#include <Utility/ImageLoader.hpp>
#include <Utility/ShaderRegistry.hpp>

#include <Drawing/TextureTiled.hpp>
#include <Receivers/Element.hpp>

namespace etudes {

    class TextureTiled;

    class ImageView : public Element {
    public:
        ImageView(std::string filename);

        void registerInputs() override;

        void init() override;
        void draw() override;

    private:
        std::string filename;
        std::unique_ptr<TextureTiled> texture;

        ShaderRegistry registry;
    };
}

#endif // ETUDES_IMAGEVIEW
