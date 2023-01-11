#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, 
    GLenum shaderType){
    auto shader = ShaderUPtr(new Shader());
    if(!shader->LoadFile(filename, shaderType))
        return nullptr; //shader는 uptr이므로 return 하는순간 스코프 벗어나므로 메모리 해제됨
    return std::move(shader); //소유권 이전
}

Shader::~Shader()
{
    if(m_shader){
       glDeleteShader(m_shader); 
    }
}

bool Shader::LoadFile(const std::string &filename, GLenum shaderType)
{
    auto result = LoadTextFile(filename);
    if(!result.has_value()){
        return false;
    }

    auto& code = result.value();
    const char* codePtr = code.c_str(); //c_str():포인터 반환 
    int32_t codeLength = (int32_t)code.length(); //명시적으로 bit수를 표현

    //create and compile shader

    m_shader = glCreateShader(shaderType); //셰이더를 만들고 핸들값을 받음
    //glShader는 여러 소스코드를 넣을수있다.여기서는 1개만 넣음
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader); //컴파일

    //check compile error
    int success = 0;
    //iv : v는 pointer, 인자가 int-pointer
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader:\"{}\"", filename);
        SPDLOG_ERROR("reason : {}", infoLog);
        return false;
    }
    return true;
}