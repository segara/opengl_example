#include "context.h"

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if(!context -> Init())
    {
        return nullptr;
    }
    return std::move(context);
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT); //색상버퍼를 클리어하라
    glUseProgram(m_program->Get());
    //현재 설정된 program, vbo, vao로 그림을 그린다.
    glDrawArrays(GL_TRIANGLES, 0, 3); 
}
bool Context::Init()
{
    float vertices[] ={
        -0.5f, -0.5f, 0.0f, //왼쪽아래
        0.5f, -0.5f, 0.0f, //오른쪽아래
        0.0f, 0.5f, 0.0f, //위
    };
    //vertex array object(vao) : vbo 만들기 전에 만들어준다.
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);


    //vertex buffer object 를 만든다.
    glGenBuffers(1, &m_vertexBuffer);
    //vertex buffer의 용도 및 사용시작을 지정: array_buffer(주로 vertex데이터)
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    //위의 버퍼에 데이터를 넣는다.
    //GL_STATIC_DRAW: 버퍼 데이터를 안바꿈
    //GL_DYNAMIC_DRAW:바꿈
    //GL_STREAM_DRAW: 한번 세팅되고 몇번쓰고 버려진다.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 9, vertices, GL_STATIC_DRAW);
  
    //0번 attribute를 사용한다.
    glEnableVertexAttribArray(0);
    //0번 attribute에 대한 정의
    //3개의 float, offset은 0번(위의 vertices에서 0번째 부터)
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(float)*3,0);

    
    //정점에 대한 다양한 데이터를 gpu가 접근 가능한 메모리에 저장해 둔다.
    ShaderPtr vertShader = Shader::CreateFromFile("../shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("../shader/simple.fs", GL_FRAGMENT_SHADER);

    if(!vertShader||!fragShader){
        return false;
    }

    SPDLOG_INFO("vertex shader id : {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id : {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if(!m_program) return false;

    SPDLOG_INFO("program id : {}", m_program->Get());

    glClearColor(0.0f, 0.1f, 0.2f,0.0f); //버퍼를 클리어할때 무슨색으로 지울까

   
    return true;
}


