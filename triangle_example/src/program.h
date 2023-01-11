#ifndef __PROGRAM_H__
#define __PROGRAM_H__
#include "common.h"
#include "shader.h"

CLASS_PTR(Program);
class Program{
public:
    //ShaderPtr 사용: Shader인스턴스는 다른 Program 인스턴스를 만드는데 재사용할수있음
    //따라서 Shared pointer 사용
    static ProgramUPtr Create(const std::vector<ShaderPtr>& shaders);

    ~Program();
    uint32_t Get() const {return m_program;}

private:
    Program(){}
    //초기화
    //여러개의 Shader를 링크

    bool Link(const std::vector<ShaderPtr>& shaders);
    uint32_t m_program {0}; //opengl이 return하는 셰이더 id

};

#endif