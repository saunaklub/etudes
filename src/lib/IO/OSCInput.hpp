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

#ifndef ETUDES_OSCINPUT
#define ETUDES_OSCINPUT

#include <memory>
#include <map>

#include <lo/lo.h>

#include "OSCInput.hpp"


namespace etudes {

    class Receiver;

    class OSCInput {

    public:

        using receiver_map_t = std::map<std::string, std::shared_ptr<Receiver>>;

        OSCInput(int port);
        virtual ~OSCInput();

        void start();
        void stop();

        template <typename T>
        void update(std::string path,
                    const T &values);

        bool addReceiver(std::string name, std::shared_ptr<Receiver> receiver);

    private:

        receiver_map_t receivers;

        int port;
        lo_server_thread oscServer;

        bool started;
    };

}

#endif // ETUDES_OSCINPUT
