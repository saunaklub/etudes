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

#include <vector>

#include <iostream>
#include <fstream>

#include <glbinding/gl/gl.h>
using namespace gl;

#include <Utility/Logging.hpp>
#include "ShaderRegistry.hpp"

using namespace std::literals::string_literals;

namespace {
    void readFileIntoString(std::string filename, std::string &result) {
        std::ifstream file(filename);
        if(file) {
            // get size of file
            file.seekg(0, std::ios::end);
            std::streampos length = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(length);
            file.read(&buffer[0],length);

            result = std::string(buffer.begin(), buffer.end());
        }
    }
}

namespace etudes {

    GLuint ShaderRegistry::registerShader(
        std::string name,
        GLenum type,
        std::vector<std::string> paths) {

        log(logging::debug, "Registering shader: "s + name);

        // create gl shader object
        GLuint shader = glCreateShader(type);

        std::string sShader;
        std::string sShaderCombined;
        for(std::string &path: paths) {
            // read data from path
            readFileIntoString(path, sShader);
            sShaderCombined += sShader;
        }

        const char* strShaderData = sShaderCombined.c_str();
        glShaderSource(shader, 1, &strShaderData, NULL);

        log(logging::debug, "Shader source:\n"s + strShaderData + "\n");

        glCompileShader(shader);

        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if(status == 0) {
            GLint infoLogLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::vector<GLchar> sInfoLog;
            sInfoLog.reserve(infoLogLength+1);
            glGetShaderInfoLog(shader, infoLogLength,
                               NULL, &sInfoLog.front());

            std::string sShaderType;
            switch(type) {
            case GL_VERTEX_SHADER: sShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER: sShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: sShaderType = "fragment"; break;
            case GL_COMPUTE_SHADER: sShaderType = "compute"; break;
            default: break;
            }

            std::cerr << "Compile failure in " << sShaderType
                      << " shader: " << name << std::endl
                      << &sInfoLog.front() << std::endl;
        }

        m_mapShader[name] = shader;
        return shader;
    }

    GLuint ShaderRegistry::registerProgram(
        std::string name,
        std::vector<std::string> shader_names) {

        log(logging::debug, "Registering program: "s + name);

        GLuint program = glCreateProgram();

        for(auto & shaderName : shader_names)
            glAttachShader(program,m_mapShader[shaderName]);

        glLinkProgram(program);

        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        if(status == 0) {
            GLint infoLogLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

            std::vector<GLchar> sInfoLog;
            sInfoLog.reserve(infoLogLength+1);

            glGetProgramInfoLog(program, infoLogLength,
                                NULL, &sInfoLog.front());

            std::cerr << "Linker failure: " << &sInfoLog.front() << std::endl;
        }

        for(size_t iLoop = 0; iLoop < shader_names.size(); iLoop++)
            glDetachShader(program, m_mapShader[shader_names[iLoop]]);

        m_mapProgram[name] = program;
        return program;
    }

    GLuint ShaderRegistry::registerUniform(std::string program_name,
                                           std::string uniform_name) {
        GLuint location = glGetUniformLocation(getProgram(program_name),
                                               uniform_name.c_str());
        m_mapUniform[program_name][uniform_name] = location;
        return location;
    }

    GLuint ShaderRegistry::getProgram(std::string name) {
        std::map<std::string, GLuint>::iterator it = m_mapProgram.find(name);

        if(it == m_mapProgram.end()) {
            log(logging::debug, "Program "s + name +
                " not found in ShaderRegistry!");
            return ~0;
        }

        return it->second;
    }

    GLuint ShaderRegistry::getUniform(std::string program_name,
                                      std::string uniform_name) {
        return m_mapUniform[program_name][uniform_name];
    }

}