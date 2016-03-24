#ifndef ETUDES_IMAGEVIEW
#define ETUDES_IMAGEVIEW

#include <memory>

#include <Utility/ImageLoader.hpp>

#include <Rendering/Texture.hpp>
#include <Receivers/Element.hpp>

namespace etudes {

    class TextureTiled;

    class ImageView : public Element {
    public:
        ImageView(std::string filename);

        void registerInputs() override;

        void init() override;
        void draw(const Painter &painter) override;

    private:
        void uploadTextureData();

        std::string filename;

        std::unique_ptr<ImageLoader> loader;
        std::unique_ptr<Texture> texture;
    };
}

#endif // ETUDES_IMAGEVIEW
