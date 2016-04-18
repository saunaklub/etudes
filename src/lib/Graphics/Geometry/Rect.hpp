#ifndef ETUDES_RECT
#define ETUDES_RECT

#include <string>

namespace etudes {
    class Rect {
    public:
        enum Scaling {
            STRETCH,
            CROP,
            BORDER
        };

        Rect();
        Rect(float x, float y, float width, float height);

        float getPosX() const;
        float getPosY() const;

        float getWidth() const;
        float getHeight() const;

        void setPosX(float x);
        void setPosY(float y);

        void setWidth(float width);
        void setHeight(float height);

        Rect maximizedTo(const Rect &rect, Scaling scaling) const;

        std::string toString() const;

    private:
        float x, y;
        float width, height;
    };

    std::ostream &operator<<(std::ostream &os,
                             const Rect &t);
}

#endif // ETUDES_RECT
