/*

  Études Audiovisuelles - Graphical elements for audiovisual composition.
  Copyright (C) 2015-2016 Patric Schmitz

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ETUDES_ELEMENT
#define ETUDES_ELEMENT

#include <Graphics/Context.hpp>
#include <Graphics/Painter.hpp>

#include <Receivers/Receiver.hpp>

namespace etudes {

    class Context;
    class Painter;

    class Element : public Receiver {
    public:
        Element();
        virtual ~Element() {};

        virtual void init() {};
        virtual void update() {};
        virtual void draw() = 0;

        void setContext(const Context & context);
        const Context & getContext() const;

    protected:
        ShaderRegistry & getShaderRegistry();
        Painter & getPainter();

    private:
        const Context * context;

        ShaderRegistry shaders;
        Painter painter;
    };

}

#endif // ETUDES_ELEMENT
