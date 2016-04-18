#ifndef ETUDES_IMAGEVIEW
#define ETUDES_IMAGEVIEW

#include <memory>

#include <Receivers/Element.hpp>

#include <Graphics/Image.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/PanZoom.hpp>

namespace etudes {

    class ImageView : public Element {
    public:
        ImageView(std::string filename,
                  std::unique_ptr<PanZoom> panZoom);

        void registerInputs() override;

        void init() override;
        void draw(const Context &context) override;

    private:
        std::string filename;

        std::unique_ptr<Image> image;
        std::unique_ptr<Texture> texture;

        std::unique_ptr<PanZoom> panZoom;
    };
}

#endif // ETUDES_IMAGEVIEW
