#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader{
public:
    //CreateFromFile으로만 사용, Shader(); 로 생성불가(생성자가 private)
    static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);

    ~Shader();
    uint32_t Get() const {return m_shader;}

private:
    Shader(){}
    bool LoadFile(const std::string& fileName, GLenum shaderType);
    uint32_t m_shader {0}; //opengl이 return하는 셰이더 id

};

#endif