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

#ifndef _ETUDES_OSCINPUTROUTER
#define _ETUDES_OSCINPUTROUTER

#include "OSCInputRouter.hpp"
#include <lo/lo.h>

namespace etudes {
    class OSCInputRouter {
    public:
        OSCInputRouter(int port);
        virtual ~OSCInputRouter();
        
        void start();
        void stop();

        void update();
        
    private:
        int port;
        lo_server_thread oscServer;

        bool started;
    };
}

#endif // _ETUDES_OSCINPUTROUTER