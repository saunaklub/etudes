#ifndef ETUDES_IMAGEVIEW
#define ETUDES_IMAGEVIEW

#include <memory>

#include <Receivers/Element.hpp>

#include <IO/ImageLoader.hpp>
#include <Graphics/Texture.hpp>

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
