#ifndef _SHADERREGISTRY
#define _SHADERREGISTRY

#include <vector>
#include <map>
#include <string>

#include <glbinding/gl/gl.h>

class ShaderRegistry {
    std::map<std::string, gl::GLuint> m_mapShader;
    std::map<std::string, gl::GLuint> m_mapProgram;
    std::map<std::string, std::map<std::string, GLuint> > m_mapUniform;

public:
    GLuint RegisterShader(std::string name,
                          gl::GLenum type,
                          std::vector<std::string> paths);

    GLuint RegisterProgram(std::string name,
                           std::vector<std::string> shader_names);

    GLuint RegisterUniform(std::string program_name,
                           std::string uniform_name);

    GLuint GetProgram(std::string name);
    GLuint GetUniform(std::string program_name,
                      std::string uniform_name);

};

#endif // _SHADERREGISTRY
