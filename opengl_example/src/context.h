#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"

/// @brief Program을 관리하는 클래스
/// @param  
CLASS_PTR(Context);
class Context{
public:
    static ContextUPtr Create();
    void Render();
   
private:
    Context(){}
    bool Init();
    ProgramUPtr m_program;

};

#endif