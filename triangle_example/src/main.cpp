#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "common.h"
#include "context.h"

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height)
{
   SPDLOG_INFO("framebuffer size changed:({}x{})", width, height);
   glViewport(0,0,width,height);  //윈도우 뷰포트
}
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
int main(int argc, const char** argv)
{
    SPDLOG_INFO("hello, opengl");
    if(!glfwInit())
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw:{}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //window 생성 
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if(!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    // context(rendering 관련정보를 가지는 구조체)를 생성
    // context에는 그릴 윈도우정보 또한 셋팅된다
    glfwMakeContextCurrent(window);

    //glad를 활용한 opengl함수로딩
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGl context version :{}",(char*)glVersion);
    
     auto context = Context::Create();
     if(!context){
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
     }
  
    //OnFramebufferSizeChange:최초 영역지정을 위해 on~함수를 강제 호출
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    //glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    while(!glfwWindowShouldClose(window))
    {
       // glClearColor(0.0f, 0.1f,0.2f,0.0f); //버퍼를 클리어할때 무슨색으로 지울까
        //glClear(GL_COLOR_BUFFER_BIT);//프레임버퍼클리어
        context->Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    context.reset(); //unique ptr 소유권 해제
    glfwTerminate();
    return 0;
}
//cmake 빌드 명령어
//cmake -Bbuild . -DCMAKE_BUILD_TYPE=Debug
//-B:빌드디렉토리(ex)build
// . :루트 디렉토리
//결과 : 비주얼스튜디오 프로젝트