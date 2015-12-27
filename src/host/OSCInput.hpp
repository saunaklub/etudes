/*

  Études Audiovisuel - graphical elements for audiovisual composition
  Copyright (C) 2015 Patric Schmitz, Claudio Cabral

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

#ifndef ETUDES_OSCINPUT
#define ETUDES_OSCINPUT

#include <map>

#include <lo/lo.h>

#include <Receiver/Etude.hpp>

#include "OSCInput.hpp"


namespace etudes {
    class OSCInput {
        typedef std::map<std::string, std::unique_ptr<Etude>> etude_map_t;

    public:
        OSCInput(const etude_map_t &registry, int port);
        virtual ~OSCInput();

        void start();
        void stop();

        void update(std::string path,
                    std::vector<float> values);

    private:
        const etude_map_t &registry;

        int port;
        lo_server_thread oscServer;

        bool started;
    };
}

#endif // ETUDES_OSCINPUT
