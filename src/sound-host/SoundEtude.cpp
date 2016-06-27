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

#include <iostream>
#include <iomanip>

#include <yaml-cpp/yaml.h>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
using namespace gl;

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Utility/Logging.hpp>
#include <Utility/Configuration.hpp>
#include <Receivers/Etude.hpp>

#include <IO/OSCInput.hpp>

#include "SoundEtude.hpp"

namespace etudes {
    SoundEtude::SoundEtude() :
        oscInput(etudes, 6667) {
        }

    SoundEtude::~SoundEtude() {
    }

    int outputChar(int i,int x, int t, int o){
        return( 
                (3&x&( i * ( ( 3 & i >> 16 ? "BY}6YB6%" : "Qj}6jQ6%" ) [t%8] + 51) >> o)
                ) << 4 );
    };


    void SoundEtude::initialise() {
        initOSC();
    }


    void SoundEtude::initOSC() {
        oscInput.start();
    }
}
