/*

  Études Audiovisuel - Graphical elements for audiovisual composition.
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

#ifndef ETUDES_ETUDEFACTORY
#define ETUDES_ETUDEFACTORY

#include <memory>

namespace etudes {

    class Etude;
    class Configuration;
    class Context;
    class Painter;

    class EtudeFactory {
    public:
        static std::shared_ptr<Etude>
        makeEtude(std::string name,
                  const Configuration &config,
                  const Context &context,
                  Painter &painter);

    private:
        static std::shared_ptr<Etude>
        makeEtudeDefault(const Configuration &config,
                         const Context &context,
                         Painter &painter);
    };

}

#endif // ETUDES_ETUDEFACTORY
